// Copyright Philip Dunstan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HistoricalDebuggerManagerTickActor.generated.h"

class FHistoricalDebuggerManager;

UCLASS()
class HISTORICALDEBUGGER_API AHistoricalDebuggerManagerTickActor: public AActor
{
	GENERATED_BODY()
public:
	AHistoricalDebuggerManagerTickActor(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	FHistoricalDebuggerManager* HistoricalDebuggerManager = nullptr;
};

