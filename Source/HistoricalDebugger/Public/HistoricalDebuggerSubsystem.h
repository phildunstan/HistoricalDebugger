// Copyright Philip Dunstan

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "HistoricalDebuggerDebugChannel.h"
#include "HistoricalDebuggerDebugContext.h"
#include "HistoricalDebuggerManager.h"
#include "HistoricalDebuggerSubsystem.generated.h"

class UHistoricalDebuggerSettingsDataAsset;

UCLASS(Blueprintable, Abstract)
class HISTORICALDEBUGGER_API UHistoricalDebuggerSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool IsTickableWhenPaused() const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual TStatId GetStatId() const override;

	UPROPERTY(EditDefaultsOnly, Category = "Historical Debugger")
	TObjectPtr<UHistoricalDebuggerSettingsDataAsset> HistoricalDebuggerSettingsDataAsset;

	
#if ENABLE_HISTORICALDEBUGGER
	
	static FHistoricalDebuggerManager* GetHistoricalDebuggerManager(const UWorld* const World)
	{
		if (UHistoricalDebuggerSubsystem* HistoricalDebuggerSubsystem = World->GetSubsystem<UHistoricalDebuggerSubsystem>())
			return HistoricalDebuggerSubsystem->HistoricalDebuggerManager;
		return nullptr;	
	}
	
	template <typename TChannelIdentifier>
	static FHistoricalDebuggerDebugChannel* GetDebugChannel(const UWorld* const World, const TChannelIdentifier& Identifier)
	{
		if (UHistoricalDebuggerSubsystem* HistoricalDebuggerSubsystem = World->GetSubsystem<UHistoricalDebuggerSubsystem>())
			return HistoricalDebuggerSubsystem->HistoricalDebuggerManager->GetDebugChannel(Identifier);
		return nullptr;
	}
	
private:
	FHistoricalDebuggerManager* HistoricalDebuggerManager = nullptr;
	
#else
	static FHistoricalDebuggerManager* GetHistoricalDebuggerManager(const UWorld* const World) { return nullptr; }
	template <typename TChannelIdentifier>
	static FHistoricalDebuggerDebugChannel* GetDebugChannel(const UWorld* const World, const TChannelIdentifier& Identifier) { return nullptr; }
#endif
};
