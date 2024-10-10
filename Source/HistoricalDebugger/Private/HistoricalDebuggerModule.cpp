#include "HistoricalDebuggerModule.h"

#include "HistoricalDebuggerManager.h"
#include "HistoricalDebuggerVisualLoggerExtension.h"

#include "ConsoleSettings.h"
#include "HistoricalDebuggerSubsystem.h"
#include "Engine/Console.h"

#define LOCTEXT_NAMESPACE "FHistoricalDebuggerModule"

FAutoConsoleCommand EnableDebugChannelCommand(
    TEXT("HistoricalDebugger.EnableDebugChannel"),
    TEXT("Enables/Disables a debug channel"),
    FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
    {
        if (Args.Num() > 0)
        {
            const FName ChannelName(*Args[0]);
			if (Args.Num() > 1)
			{
				const bool bShouldEnable = FCString::Atoi(*Args[1]) == 1;
				FHistoricalDebuggerManager::Get().SetChannelRecordingEnabled(ChannelName, bShouldEnable);
				UE_LOG(LogHistoricalDebugger, Log, TEXT("%hs debug channel %s"), (bShouldEnable ? "Enabled" : "Disabled"), *ChannelName.ToString());
			}
			else
			{
				bool bIsEnabled = FHistoricalDebuggerManager::Get().IsChannelRecordingEnabled(ChannelName);
				UE_LOG(LogHistoricalDebugger, Log, TEXT("debug channel %s is %hs"), *ChannelName.ToString(), (bIsEnabled ? "Enabled" : "Disabled"));
			}
        }
        else
        {
            UE_LOG(LogHistoricalDebugger, Warning, TEXT("Usage: DebugChannel <ChannelName> [0|1]"));
        }
    })
);

void FHistoricalDebuggerModule::StartupModule()
{
	// force initialization of the historical debugger manager
	UHistoricalDebuggerSubsystem::StaticClass()->AddToRoot();
	
	UConsole::RegisterConsoleAutoCompleteEntries.AddLambda([](TArray<FAutoCompleteCommand>& AutoCompleteList)
		{
			FHistoricalDebuggerManager& HistoricalDebuggerManager = FHistoricalDebuggerManager::Get();
			for (const FName& ChannelName : HistoricalDebuggerManager.GetAllChannelNames())
			{
				const UConsoleSettings* ConsoleSettings = GetDefault<UConsoleSettings>();
				AutoCompleteList.AddDefaulted();
				FAutoCompleteCommand& AutoCompleteCommand = AutoCompleteList.Last();
				AutoCompleteCommand.Command = *FString::Printf(TEXT("HistoricalDebugger.EnableDebugChannel %s"), *ChannelName.ToString());
				AutoCompleteCommand.Desc = TEXT("Enables/Disables a debug channel");
				AutoCompleteCommand.Color = ConsoleSettings->AutoCompleteCommandColor;
			}
		});
	
#if ENABLE_VISUAL_LOG
	FVisualLogger::Get().RegisterExtension(FName("HistoricalDebugger"), new FHistoricalDebuggerVisualLoggerExtension());
#endif
}

void FHistoricalDebuggerModule::ShutdownModule()
{
#if ENABLE_VISUAL_LOG
	FVisualLogger::Get().UnregisterExtension(FName("HistoricalDebugger"), nullptr);
#endif
	
	// if (UHistoricalDebuggerSubsystem::StaticClass()->IsRooted())
	//	UHistoricalDebuggerSubsystem::StaticClass()->RemoveFromRoot();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FHistoricalDebuggerModule, HistoricalDebugger)