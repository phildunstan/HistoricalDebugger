// Copyright Philip Dunstan


#include "HistoricalDebuggerManagerTickActor.h"

#include "HistoricalDebuggerManager.h"


AHistoricalDebuggerManagerTickActor::AHistoricalDebuggerManagerTickActor(const FObjectInitializer &ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bTickEvenWhenPaused = true;
    PrimaryActorTick.TickGroup = TG_PostUpdateWork;	
}

void AHistoricalDebuggerManagerTickActor::BeginPlay()
{
	Super::BeginPlay();
	// FHistoricalDebuggerManager::Get().Reset();
}

void AHistoricalDebuggerManagerTickActor::Tick(float DeltaSeconds)
{
	FHistoricalDebuggerManager::Get().Tick(DeltaSeconds);
}

