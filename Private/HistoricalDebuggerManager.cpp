// Fill out your copyright notice in the Description page of Project Settings.


#include "HistoricalDebuggerManager.h"

#include "HistoricalDebuggerSettingsDataAsset.h"
#include "HistoricalDebuggerRenderer.h"

#include "imgui.h"
#include "implot.h"

DEFINE_LOG_CATEGORY(LogHistoricalDebugger);

FHistoricalDebuggerManager::FHistoricalDebuggerManager()
{
#if ENABLE_HISTORICALDEBUGGER
	Renderer = new FHistoricalDebuggerRenderer;
#endif
}

FHistoricalDebuggerManager& FHistoricalDebuggerManager::Get()
{
	static FHistoricalDebuggerManager GHistoricalDebuggerManager;
	return GHistoricalDebuggerManager;
}

FHistoricalDebuggerManager::~FHistoricalDebuggerManager()
{
#if ENABLE_HISTORICALDEBUGGER
	for (auto ChannelPair : Channels)
	{
		delete ChannelPair.Value;
	}

	delete Renderer;
#endif
}

void FHistoricalDebuggerManager::Pause()
{
	SetTimeSeconds(MaxDrawTimeSeconds - 0.01f);
}

void FHistoricalDebuggerManager::Resume()
{
	SetTimeSeconds(MaxDrawTimeSeconds);
}

void FHistoricalDebuggerManager::StepForward()
{
	SetTimeSeconds(FMath::Min(DebugFilter.DrawTimeSeconds + 0.01f, MaxDrawTimeSeconds - 0.01f));
}

void FHistoricalDebuggerManager::StepBackward()
{
	SetTimeSeconds(DebugFilter.DrawTimeSeconds - 0.01f);
}

void FHistoricalDebuggerManager::SetSettings(const TObjectPtr<UHistoricalDebuggerSettingsDataAsset>& NewSettings)
{
	Settings = NewSettings;
}

bool FHistoricalDebuggerManager::IsChannelRecordingEnabled(const FName& Name)
{
	if (Settings)
	{
		if (const bool* const bIsEnabled = Settings->EnabledChannels.Find(Name))
		{
			return *bIsEnabled;
		}
		else
		{
			Settings->EnabledChannels.Add(Name, true);
			return true;
		}
	}
	
	return true;
}

void FHistoricalDebuggerManager::SetChannelRecordingEnabled(const FName& Name, const bool bNewIsEnabled)
{
	if (Settings)
	{
		if (bool* const bIsEnabled = Settings->EnabledChannels.Find(Name))
		{
			*bIsEnabled = bNewIsEnabled;
		}
	}
}

bool FHistoricalDebuggerManager::IsChannelPlaybackEnabled(const FName& Name)
{
	if (Settings)
	{
		if (const bool* const bIsEnabled = Settings->EnabledChannels.Find(Name))
		{
			return *bIsEnabled;
		}
		else
		{
			Settings->EnabledChannels.Add(Name, true);
			return true;
		}
	}
	return true;
}

void FHistoricalDebuggerManager::SetChannelPlaybackEnabled(const FName& Name, const bool bNewIsEnabled)
{
	if (Settings)
	{
		if (bool* const bIsEnabled = Settings->EnabledChannels.Find(Name))
		{
			*bIsEnabled = bNewIsEnabled;
		}
	}
}

TArray<FName> FHistoricalDebuggerManager::GetAllChannelNames() const
{
	TArray<FName> Names;
#if ENABLE_HISTORICALDEBUGGER
	Names.Reserve(Channels.Num());
	if (Settings)
	{
		Settings->EnabledChannels.GetKeys(Names);
	}
	for (const auto& ChannelPair : Channels)
	{
		Names.AddUnique(ChannelPair.Value->GetName());
	};
#endif
	return Names;
}

#if ENABLE_HISTORICALDEBUGGER
FHistoricalDebuggerDebugChannel* FHistoricalDebuggerManager::GetDebugChannel(const FName& Name)
{
	if (CurrentMode == EHistoricalDebuggerMode::Playback)
		return nullptr;
	
	if (!IsChannelRecordingEnabled(Name))
		return nullptr;
		
	FHistoricalDebuggerDebugChannel* Channel = nullptr;
	if (FHistoricalDebuggerDebugChannel** ChannelPtr = Channels.Find(Name))
	{
		Channel = *ChannelPtr;
	}
	else
	{
		Channel = Channels.Add(Name, new FHistoricalDebuggerDebugChannel(Name));
	}

	Channel->SetWorldTime(World->TimeSeconds);
	Channel->SetIteration(0);
	return Channel;
}

FHistoricalDebuggerDebugChannel * FHistoricalDebuggerManager::GetDebugChannel(const FLogCategoryBase &LogCategory)
{
	return GetDebugChannel(LogCategory.GetCategoryName());
}
#endif

void FHistoricalDebuggerManager::SetWorld(UWorld* NewWorld)
{
	World = NewWorld;
	Reset();
}

void FHistoricalDebuggerManager::SetTimeSeconds(float NewDrawTimeSeconds)
{
	if (NewDrawTimeSeconds >= MaxDrawTimeSeconds)
	{
		World->GetFirstPlayerController()->SetPause(false);
		CurrentMode = EHistoricalDebuggerMode::Recording;
		DebugFilter.DrawTimeSeconds = MaxDrawTimeSeconds;
		DebugFilter.DrawSubIteration = -1;
	}
	else
	{
		World->GetFirstPlayerController()->SetPause(true);
		CurrentMode = EHistoricalDebuggerMode::Playback;
		DebugFilter.DrawTimeSeconds = NewDrawTimeSeconds;
		DebugFilter.DrawSubIteration = -1;
	}
}

void FHistoricalDebuggerManager::Reset()
{
#if ENABLE_HISTORICALDEBUGGER
	for (const auto& ChannelPair : Channels)
	{
		FHistoricalDebuggerDebugChannel* Channel = ChannelPair.Value;
		Channel->Clear();
	}
#endif
	if (World)
	{
		MaxDrawTimeSeconds = World->TimeSeconds;
		DebugFilter.DrawTimeSeconds = MaxDrawTimeSeconds;
		DebugFilter.DrawSubIteration = -1;
		CurrentMode = EHistoricalDebuggerMode::Recording;
	}
}

void FHistoricalDebuggerManager::Tick(float DeltaTime)
{
#if ENABLE_HISTORICALDEBUGGER
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("FHistoricalDebuggerManager::Tick"))
	
	if (!World || !World->IsInitialized() || !World->IsGameWorld())
		return;

	if ((CurrentMode == EHistoricalDebuggerMode::Recording) && (DeltaTime > 0.0f))
	{
		MaxDrawTimeSeconds = World->TimeSeconds;
		DebugFilter.DrawTimeSeconds = MaxDrawTimeSeconds;
	}

	static TArray<FHistoricalDebuggerDrawCommand> DrawCommands; // reuse this buffer each frame
	
	for (const auto& ChannelPair : Channels)
	{
		const FName& ChannelName = ChannelPair.Key;
		FHistoricalDebuggerDebugChannel* Channel = ChannelPair.Value;
		
		if (!IsChannelPlaybackEnabled(ChannelName))
			continue;

		DrawCommands.Reset();
		Channel->ExtractDrawCommands(DrawCommands, DebugFilter);
		Renderer->Draw(World, DrawCommands, DrawMode, DebugFilter, bShowLabels);
		
		const float DebugWindowTimeSeconds = Settings ? Settings->DebugWindowTimeSeconds : 15.0f;
		Channel->RemoveExpiredDrawCommands(World->TimeSeconds, DebugWindowTimeSeconds);
	}

	if (Settings)
		Settings->DrawImGui();
	
	DrawImGui();
#endif
}

void FHistoricalDebuggerManager::DrawImGui()
{
#if WITH_EDITOR
	static bool ImGuiWindow = false;
	if (ImGui::Begin("Historical Debugger", &ImGuiWindow, 0))
	{
        const char* DrawModeStrings[] = { "None", "Viewport", "VisLog", "All" };
        int DrawModeInt = static_cast<int>(DrawMode);
        if (ImGui::Combo("Draw Mode", &DrawModeInt, DrawModeStrings, IM_ARRAYSIZE(DrawModeStrings)))
        {
            DrawMode = static_cast<EHistoricalDebuggerDrawMode>(DrawModeInt);
        }

		ImGui::Checkbox("Show Labels", &bShowLabels);

		static char IdFilterIncludeInputBuffer[128] = { 0 };
        if (ImGui::InputText("ID Filter Include", IdFilterIncludeInputBuffer, 128, ImGuiInputTextFlags_AutoSelectAll))
        {
        	DebugFilter.IdFilterInclude = IdFilterIncludeInputBuffer;
        }
		
		static char IdFilterExcludeInputBuffer[128] = { 0 };
        if (ImGui::InputText("ID Filter Exclude", IdFilterExcludeInputBuffer, 128, ImGuiInputTextFlags_AutoSelectAll))
        {
        	DebugFilter.IdFilterExclude = IdFilterExcludeInputBuffer;
        }

		ImGui::InputInt("Sub-Iteration", &DebugFilter.DrawSubIteration);
		
		if (ImPlot::BeginPlot("", ImVec2(-1, 100), ImPlotFlags_NoTitle | ImPlotFlags_NoLegend | ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect))
		{
			const float DebugWindowTimeSeconds = Settings ? Settings->DebugWindowTimeSeconds : 15.0f;
			static TArray<FName> ChannelNames;
			ChannelNames.Reset();
			static TArray<float> PlotX;
			PlotX.Reset();
			static TArray<float> PlotY;
			PlotY.Reset();

			for (const auto& ChannelPair : Channels)
			{
				FHistoricalDebuggerDebugChannel* Channel = ChannelPair.Value;
				
				static TArray<float> DataTimes;
				DataTimes.Reset();
				Channel->ExtractDataTimes(DataTimes);
				if (DataTimes.IsEmpty())
					continue;
				
				const FName& ChannelName = ChannelPair.Key;
				const int ChannelIndex = ChannelNames.Add(ChannelName);
				
				for (const float Time : DataTimes)
				{
					PlotX.Add(Time);
					PlotY.Add(ChannelIndex);
				}
			}

			if (CurrentMode == EHistoricalDebuggerMode::Recording)
			{
				ImPlot::SetupAxis(ImAxis_X1, nullptr, ImPlotAxisFlags_NoInitialFit | ImPlotAxisFlags_NoMenus | ImPlotAxisFlags_NoSideSwitch);
				constexpr float PlotTimeMarginSeconds = 1.0f;
				ImPlot::SetupAxisLimits(ImAxis_X1, World->TimeSeconds - DebugWindowTimeSeconds + PlotTimeMarginSeconds, World->TimeSeconds + PlotTimeMarginSeconds, ImPlotCond_Always);
			}
			else
			{
				ImPlot::SetupAxis(ImAxis_X1, nullptr, ImPlotAxisFlags_PanStretch | ImPlotAxisFlags_NoInitialFit | ImPlotAxisFlags_NoMenus | ImPlotAxisFlags_NoSideSwitch );
			}
			
			ImPlot::SetupAxis(ImAxis_Y1, nullptr, ImPlotAxisFlags_NoInitialFit | ImPlotAxisFlags_NoMenus | ImPlotAxisFlags_NoSideSwitch | ImPlotAxisFlags_Invert | ImPlotAxisFlags_Lock);
			ImPlot::SetupAxisLimits(ImAxis_Y1, -0.5f, ChannelNames.Num() - 0.5f, ImPlotCond_Always);
			auto GetLabelForChannel =  [] (double Value, char* Buffer, int Size, void* UserData) -> int
			{
				const TArray<FName>* ChannelNamesPtr = static_cast<const TArray<FName>*>(UserData);
				const int Index = static_cast<int>(Value);
				if (Index >= 0 && Index < ChannelNamesPtr->Num())
				{
					const FString ChannelName = (*ChannelNamesPtr)[Index].ToString();
					FCStringAnsi::Strncpy(Buffer, TCHAR_TO_ANSI(*ChannelName), Size);
				}
				return 0;
			};
			ImPlot::SetupAxisFormat(ImAxis_Y1, GetLabelForChannel, &ChannelNames);
			ImPlot::SetupAxisTicks(ImAxis_Y1, 0, ChannelNames.Num() - 1, ChannelNames.Num(), nullptr, false);
			
			ImPlot::SetupFinish();
			
			ImPlot::PlotScatter("", PlotX.GetData(), PlotY.GetData(), PlotX.Num());

			const double MaxTimeSeconds = World->GetTimeSeconds();
			const double MinTimeSeconds = World->GetTimeSeconds() - DebugWindowTimeSeconds;
			ImPlot::PlotInfLines("Min Time", &MinTimeSeconds, 1);
			ImPlot::PlotInfLines("Max Time", &MaxTimeSeconds, 1);
				
			double CurrentDebugTimeSeconds = GetDebugTimeSeconds();
			if (GetCurrentMode() == EHistoricalDebuggerMode::Playback)
			{
				ImPlot::PlotInfLines("Current Time", &CurrentDebugTimeSeconds, 1);
			}
			
			if (ImPlot::DragLineX(0, &CurrentDebugTimeSeconds, ImVec4(1, 1, 0, 1)))
			{
				SetTimeSeconds(CurrentDebugTimeSeconds);
			}
			else
			{
				if (ImPlot::IsPlotHovered() && ImGui::IsMouseClicked(0))
				{
					const ImPlotPoint mousePos = ImPlot::GetPlotMousePos();
					SetTimeSeconds(mousePos.x);
				}
			}
			
			ImPlot::EndPlot();
		}

		if (ImGui::Button("Step Backwards"))
		{
			StepBackward();
		}

		ImGui::SameLine();
		
		if (ImGui::Button("Step Forwards"))
		{
			StepForward();
		}
		
		ImGui::SameLine();
		
		if (ImGui::Button("Pause/Resume"))
		{
			if (CurrentMode == EHistoricalDebuggerMode::Recording)
				Pause();
			else if (CurrentMode == EHistoricalDebuggerMode::Playback)
				Resume();
		}

		ImGui::Text("%.4f", GetDebugTimeSeconds());
		
		ImGui::End();
	}
#endif
}


