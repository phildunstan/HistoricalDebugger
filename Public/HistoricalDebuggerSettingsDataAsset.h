// Copyright Philip Dunstan

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HistoricalDebuggerSettingsDataAsset.generated.h"

class FProperty;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class HISTORICALDEBUGGER_API UHistoricalDebuggerSettingsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UHistoricalDebuggerSettingsDataAsset();
	FString GetDisplayName() const;

	bool SaveDataAsset(const FString& SavePath);
	
	void DrawImGui();
	void DrawPropertyImGui(const FProperty& Property);

	/** Time (seconds) that debug is held. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float DebugWindowTimeSeconds = 15.0f;
	
	/** Specifies whether a channel is enabled for both Recording and Playback. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Channels")
	TMap<FName, bool> EnabledChannels;
};
