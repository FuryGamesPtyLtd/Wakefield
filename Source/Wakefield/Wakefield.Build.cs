using UnrealBuildTool;

public class Wakefield : ModuleRules
{
    public Wakefield(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        IWYUSupport = IWYUSupport.Full;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
    }
}
