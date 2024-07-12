using UnrealBuildTool;

public class HistoricalDebugger : ModuleRules
{
    public HistoricalDebugger(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange( new string[] { "Core", } );
        
		PublicDependencyModuleNames.AddRange(new string[] { "ImGui" });
		// Tell the compiler we want to import the ImPlot symbols when linking against ImGui plugin 
		PrivateDefinitions.Add(string.Format("IMPLOT_API=DLLIMPORT"));
		
        PrivateDependencyModuleNames.AddRange( new string[] { "CoreUObject", "Engine", "EngineSettings", "Slate", "SlateCore" } );

		// PublicDefinitions.Add("SHIPPING_DRAW_DEBUG_ERROR=1");
    }
}