// Copyright Philip Dunstan


#include "HistoricalDebuggerSubsystem.h"

#include "HistoricalDebuggerManager.h"
#include "HistoricalDebuggerVisualLogDevice.h"
#include "VisualLogger/VisualLogger.h"

bool UHistoricalDebuggerSubsystem::IsTickableWhenPaused() const
{
	return true;
}

void UHistoricalDebuggerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
#if ENABLE_HISTORICALDEBUGGER
	HistoricalDebuggerManager = &FHistoricalDebuggerManager::Get();
	HistoricalDebuggerManager->SetSettings(HistoricalDebuggerSettingsDataAsset);
#endif
	
#if ENABLE_VISUAL_LOG
	FVisualLogger& VisualLogger = FVisualLogger::Get();
	VisualLogger.AddDevice(new FHistoricalDebuggerVisualLogDevice());
#endif
	
	Super::Initialize(Collection);
}

void UHistoricalDebuggerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UHistoricalDebuggerSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
#if ENABLE_HISTORICALDEBUGGER
	HistoricalDebuggerManager->SetWorld(&InWorld);
#endif
	Super::OnWorldBeginPlay(InWorld);
}

void UHistoricalDebuggerSubsystem::Tick(float DeltaTime)
{
	FHistoricalDebuggerManager::Get().Tick(DeltaTime);
}

TStatId UHistoricalDebuggerSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UHistoricalDebugSubsystem, STATGROUP_Tickables);
}
