// DedicatedX.Build.cs

using UnrealBuildTool;

public class DedicatedX : ModuleRules
{
	public DedicatedX(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			// Initial Dependencies
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",

			// UI
			"UMG",
		});

		PublicIncludePaths.AddRange(new string[]
		{
			"DedicatedX",
		});

	}
}
