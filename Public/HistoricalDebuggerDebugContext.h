// Copyright Philip Dunstan

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EHistoricalDebuggerDebugFramePersistence : uint8
{
	All			UMETA(DisplayName = "ALL"),
	Unique		UMETA(DisplayName = "UNIQUE")
};

class HISTORICALDEBUGGER_API FHistoricalDebuggerDebugContext
{
public:
	FString Id;
	const AActor* Actor = nullptr;
	int SubIteration = -1;
	EHistoricalDebuggerDebugFramePersistence FramePersistence = EHistoricalDebuggerDebugFramePersistence::Unique;
};

