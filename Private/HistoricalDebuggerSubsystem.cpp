// Copyright Philip Dunstan


#include "HistoricalDebuggerSubsystem.h"

#include "HistoricalDebuggerManager.h"

bool UHistoricalDebuggerSubsystem::IsTickableWhenPaused() const
{
	return true;
}

void UHistoricalDebuggerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	HistoricalDebuggerManager = &FHistoricalDebuggerManager::Get();
	HistoricalDebuggerManager->SetSettings(HistoricalDebuggerSettingsDataAsset);
	Super::Initialize(Collection);
}

void UHistoricalDebuggerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UHistoricalDebuggerSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	HistoricalDebuggerManager->SetWorld(&InWorld);
}

void UHistoricalDebuggerSubsystem::Tick(float DeltaTime)
{
	FHistoricalDebuggerManager::Get().Tick(DeltaTime);
}

TStatId UHistoricalDebuggerSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UHistoricalDebugSubsystem, STATGROUP_Tickables);
}
