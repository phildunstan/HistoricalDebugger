// Copyright Philip Dunstan


#include "HistoricalDebuggerImGui.h"

#include "HistoricalDebuggerImGuiQueue.h"
#include "HistoricalDebuggerManager.h"

#include "ImGui.h"

namespace HistoricalDebuggerImGui
{
	template <typename ValueType>
	void GetValue(const FString& Id, ValueType& Value)
	{
#if ENABLE_HISTORICALDEBUGGER
		FHistoricalDebuggerManager& HistoricalDebuggerManager = FHistoricalDebuggerManager::Get();
		FHistoricalDebuggerImGuiQueue& ImGuiQueue = HistoricalDebuggerManager.GetImGuiQueue();
		if (HistoricalDebuggerManager.GetCurrentMode() == EHistoricalDebuggerMode::Playback)
		{
			ImGuiQueue.GetValue(Id, HistoricalDebuggerManager.GetDebugTimeSeconds(), Value);
		}
		else
		{
			ImGuiQueue.AddValue(Id, HistoricalDebuggerManager.GetDebugTimeSeconds(), Value);
		}
#else
		// do nothing to Value if the debugger is not enabled, this will just pass the value unchanged through to ImGui
#endif
	}

	bool Begin(const TCHAR* Name, bool* Open, ImGuiWindowFlags Flags)
	{
		return ImGui::Begin(TCHAR_TO_ANSI(Name), Open, Flags);
	}

	void End()
	{
		ImGui::End();
	}

	void RecordedTextUnformatted(const FString& Id, FString& Text)
    {
    	GetValue(Id, Text);
		ImGui::TextUnformatted(TCHAR_TO_ANSI(*Text));
    }
}
