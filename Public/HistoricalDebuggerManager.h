// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HistoricalDebuggerDebugChannel.h"
#include "HistoricalDebuggerImGuiQueue.h"
#include "HistoricalDebuggerRenderer.h"

// #define ENABLE_HISTORICALDEBUGGER (PLATFORM_DESKTOP && !NO_LOGGING && UE_ENABLE_DEBUG_DRAWING)
#define ENABLE_HISTORICALDEBUGGER WITH_EDITOR

class UWorld;
class FHistoricalDebuggerDebugChannel;
class FHistoricalDebuggerRenderer;
class UHistoricalDebuggerSettingsDataAsset;
struct FNoLoggingCategory;


HISTORICALDEBUGGER_API DECLARE_LOG_CATEGORY_EXTERN(LogHistoricalDebugger, Log, All);

enum class EHistoricalDebuggerMode
{
	Recording,
	Playback
};

class HISTORICALDEBUGGER_API FHistoricalDebuggerDebugFilter
{
public:
	float DrawTimeSeconds = 0.0f;
	int DrawSubIteration = -1;
	FString IdFilterInclude;
	FString IdFilterExclude;
	const AActor* Actor = nullptr;
};

class HISTORICALDEBUGGER_API FHistoricalDebuggerManager
{
public:
	static FHistoricalDebuggerManager& Get();
	
	~FHistoricalDebuggerManager();

	//FHistoricalDebuggerManager(const FHistoricalDebuggerManager&) = delete;
	//FHistoricalDebuggerManager(FHistoricalDebuggerManager&&) = delete;
	//FHistoricalDebuggerManager& operator=(const FHistoricalDebuggerManager&) = delete;
	//FHistoricalDebuggerManager& operator=(FHistoricalDebuggerManager&&) = delete;
	
	EHistoricalDebuggerMode GetCurrentMode() const { return CurrentMode; }

	void Pause();
	void Resume();
	void StepForward();
	void StepBackward();
	
	void SetSettings(const TObjectPtr<UHistoricalDebuggerSettingsDataAsset>& NewSettings);

	bool IsChannelRecordingEnabled(const FName& Name);
	void SetChannelRecordingEnabled(const FName& Name, const bool bNewIsEnabled);
	
	bool IsChannelPlaybackEnabled(const FName& Name);
	void SetChannelPlaybackEnabled(const FName& Name, const bool bNewIsEnabled);
	
	TArray<FName> GetAllChannelNames() const;

#if ENABLE_HISTORICALDEBUGGER
	FHistoricalDebuggerDebugChannel* GetDebugChannel(const FName& Name);
	FHistoricalDebuggerDebugChannel* GetDebugChannel(const FLogCategoryBase& LogCategory);
	
	FHistoricalDebuggerImGuiQueue& GetImGuiQueue() { return ImGuiQueue; }
#else
	FHistoricalDebuggerDebugChannel* GetDebugChannel(const FName& Name) { return nullptr; }
	FHistoricalDebuggerDebugChannel* GetDebugChannel(const FLogCategoryBase& LogCategory) { return nullptr; }
	FHistoricalDebuggerDebugChannel* GetDebugChannel(const FNoLoggingCategory& LogCategory) { return nullptr; }
#endif

	void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld);

	void SetTimeSeconds(float NewDrawTimeSeconds);
	float GetDebugTimeSeconds() const { return DebugFilter.DrawTimeSeconds; }
	
	void Reset();
	
	void Tick(float DeltaTime);

	void DrawImGui();

	FHistoricalDebuggerDebugFilter DebugFilter;
	
private:
	FHistoricalDebuggerManager();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHistoricalDebuggerSettingsDataAsset> Settings;
	
	UWorld* World = nullptr;
	
#if ENABLE_HISTORICALDEBUGGER
	TMap<FName, FHistoricalDebuggerDebugChannel*> Channels;
	
	FHistoricalDebuggerImGuiQueue ImGuiQueue;
#endif
	
	EHistoricalDebuggerMode CurrentMode = EHistoricalDebuggerMode::Recording;

	EHistoricalDebuggerDrawMode DrawMode = EHistoricalDebuggerDrawMode::All;
	float MaxDrawTimeSeconds = 0.0f;
	bool bShowLabels = false;

	FHistoricalDebuggerRenderer* Renderer = nullptr;;
};
