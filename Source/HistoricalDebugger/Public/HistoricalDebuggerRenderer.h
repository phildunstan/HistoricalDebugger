// Copyright Philip Dunstan

#pragma once

#include "CoreMinimal.h"

class FHistoricalDebuggerDrawCommand;
class FHistoricalDebuggerDebugFilter;

enum class EHistoricalDebuggerDrawMode : int
{
	None = 0,
	Viewport = 1,
	VisLog = 2,
	All = 3,
};

class HISTORICALDEBUGGER_API FHistoricalDebuggerRenderer
{
public:
	FHistoricalDebuggerRenderer();
	~FHistoricalDebuggerRenderer();
	
	void Draw(const UWorld* World, const TArray<FHistoricalDebuggerDrawCommand>& DrawCommands, const EHistoricalDebuggerDrawMode DrawMode, const FHistoricalDebuggerDebugFilter& DebugFilter, const bool bShowLabels) const;

private:
	float CommandLifetime(const FHistoricalDebuggerDrawCommand& Command, const bool bIsPaused) const;
};
