// Fill out your copyright notice in the Description page of Project Settings.

#include "HistoricalDebuggerVisualLoggerExtension.h"

#include "HistoricalDebuggerManager.h"

#if ENABLE_VISUAL_LOG

FHistoricalDebuggerVisualLoggerExtension::FHistoricalDebuggerVisualLoggerExtension()
{
	HistoricalDebuggerManager = &FHistoricalDebuggerManager::Get();
}

FHistoricalDebuggerVisualLoggerExtension::~FHistoricalDebuggerVisualLoggerExtension()
{
}

void FHistoricalDebuggerVisualLoggerExtension::DrawData(IVisualLoggerEditorInterface* EdInterface, UCanvas* Canvas)
{
	// if (UWorld* World = EdInterface->GetWorld())
	// The HistoricalDebuggerManager is ticked by a separate Actor, so we don't need to tick it here
	// HistoricalDebuggerManager->Tick(0.0f);
}

void FHistoricalDebuggerVisualLoggerExtension::OnItemsSelectionChanged(IVisualLoggerEditorInterface* EdInterface)
{
	// HistoricalDebuggerManager->DebugFilter.Actor = EdInterface->GetHelperActor();
}

void FHistoricalDebuggerVisualLoggerExtension::OnLogLineSelectionChanged(IVisualLoggerEditorInterface* EdInterface, TSharedPtr<FLogEntryItem> SelectedItem, int64 UserData)
{
	FVisualLogExtensionInterface::OnLogLineSelectionChanged(EdInterface, SelectedItem, UserData);
}

void FHistoricalDebuggerVisualLoggerExtension::OnScrubPositionChanged(IVisualLoggerEditorInterface* EdInterface, double NewScrubPosition, bool bScrubbing)
{
	HistoricalDebuggerManager->SetTimeSeconds(NewScrubPosition);
}

void FHistoricalDebuggerVisualLoggerExtension::ResetData(IVisualLoggerEditorInterface* EdInterface)
{
	HistoricalDebuggerManager->Reset();
}

#endif
