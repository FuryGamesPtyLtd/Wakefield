using UnrealBuildTool;

public class Wakefield : ModuleRules
{
	public Wakefield(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnforceIWYU = true;
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core",
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
		});
	}
}
