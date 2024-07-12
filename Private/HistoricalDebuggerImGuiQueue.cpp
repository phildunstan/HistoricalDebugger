// Copyright Philip Dunstan


#include "HistoricalDebuggerImGuiQueue.h"

void FHistoricalDebuggerImGuiQueue::Clear()
{
	FScopeLock Lock(&CommandQueueCS);
	CommandQueue.Reset();
}
