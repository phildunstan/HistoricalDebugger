#pragma once

#include "VisualLogger/VisualLoggerTypes.h"

#if ENABLE_VISUAL_LOG

class FHistoricalDebuggerVisualLogDevice : public FVisualLogDevice
{
public:
	virtual ~FHistoricalDebuggerVisualLogDevice() override;
	
	virtual void Serialize(const UObject* LogOwner, FName OwnerName, FName InOwnerClassName, const FVisualLogEntry& LogEntry) override;
	virtual void Cleanup(bool bReleaseMemory) override;
	
	virtual void StartRecordingToFile(double TimeStamp) override;
	virtual void StopRecordingToFile(double TimeStamp) override;
	virtual void DiscardRecordingToFile() override;
	virtual void SetFileName(const FString &InFileName) override;
	
	virtual void GetRecordedLogs(TArray<FVisualLogDevice::FVisualLogEntryItem> &OutLogs) const override;
	virtual bool HasFlags(int32 InFlags) const override;
};

#endif
