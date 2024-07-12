// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HistoricalDebuggerDebugContext.h"

class AActor;
class UWorld;

class HISTORICALDEBUGGER_API FHistoricalDebuggerImGuiCommand
{
public:
	FHistoricalDebuggerImGuiCommand() noexcept = default;
	
	template <typename ValueType>
	FHistoricalDebuggerImGuiCommand(const FString& Id, const float DebugTimeSeconds, const ValueType& Value)
		: Id(Id)
		, WorldTimeSeconds(DebugTimeSeconds)
	{
		Data.Set<ValueType>(Value);
	}
	
	FHistoricalDebuggerImGuiCommand(const FHistoricalDebuggerImGuiCommand& Other) noexcept = default;
	FHistoricalDebuggerImGuiCommand(FHistoricalDebuggerImGuiCommand&& Other) noexcept = default;
	FHistoricalDebuggerImGuiCommand& operator=(const FHistoricalDebuggerImGuiCommand& Other) = delete;
	
	FString Id;
	float WorldTimeSeconds = 0.0f;

	// enum class EValueType
	// {
	// 	None,
	// 	String,
	// };
	// EValueType Type = EValueType::None;

	TVariant<FString> Data;
};

class HISTORICALDEBUGGER_API FHistoricalDebuggerImGuiQueue
{
public:
	FHistoricalDebuggerImGuiQueue() = default;

	void Clear();
	
	template <typename ValueType>
	void AddValue(const FString& Id, const float DebugTimeSeconds, const ValueType& Value);
	
	template <typename ValueType>
	bool GetValue(const FString& Id, const float DebugTimeSeconds, ValueType& Value) const;

private:
	TArray<FHistoricalDebuggerImGuiCommand> CommandQueue;
	mutable FCriticalSection CommandQueueCS;
};


template <typename ValueType>
void FHistoricalDebuggerImGuiQueue::AddValue(const FString &Id, const float DebugTimeSeconds, const ValueType& Value)
{
	FScopeLock Lock(&CommandQueueCS);
	CommandQueue.Add({ Id, DebugTimeSeconds, Value });
}

template <typename ValueType>
bool FHistoricalDebuggerImGuiQueue::GetValue(const FString &Id, const float DebugTimeSeconds, ValueType& Value) const
{
	FScopeLock Lock(&CommandQueueCS);
	int Index = CommandQueue.Num() - 1;
	while (Index >= 0)
	{
		const FHistoricalDebuggerImGuiCommand& Command = CommandQueue[Index];
		if (Command.WorldTimeSeconds <= DebugTimeSeconds)
			break;
		--Index;
	}
	while (Index >= 0)
	{
		const FHistoricalDebuggerImGuiCommand& Command = CommandQueue[Index];
		if (Command.Id == Id)
		{
			Value = Command.Data.Get<ValueType>();
			return true;
		}
		--Index;
	}
	return false;
}
