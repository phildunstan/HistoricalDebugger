// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HistoricalDebuggerManager.h"

#include "VisualLogger/VisualLoggerTypes.h"

#if ENABLE_VISUAL_LOG
class FHistoricalDebuggerVisualLoggerExtension : public FVisualLogExtensionInterface
{
public:
	FHistoricalDebuggerVisualLoggerExtension();
	virtual ~FHistoricalDebuggerVisualLoggerExtension() override;
	virtual void DrawData(IVisualLoggerEditorInterface *EdInterface, UCanvas *Canvas) override;
	virtual void OnItemsSelectionChanged(IVisualLoggerEditorInterface *EdInterface) override;
	virtual void OnLogLineSelectionChanged(IVisualLoggerEditorInterface *EdInterface, TSharedPtr<FLogEntryItem> SelectedItem, int64 UserData) override;
	virtual void OnScrubPositionChanged(IVisualLoggerEditorInterface *EdInterface, double NewScrubPosition, bool bScrubbing) override;
	virtual void ResetData(IVisualLoggerEditorInterface *EdInterface) override;
	
private:
	FHistoricalDebuggerManager* HistoricalDebuggerManager = nullptr;
};
#endif
