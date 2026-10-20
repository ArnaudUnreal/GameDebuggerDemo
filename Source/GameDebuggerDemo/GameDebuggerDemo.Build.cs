using UnrealBuildTool;

public class GameDebuggerDemo : ModuleRules
{
	public GameDebuggerDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"HealthSystem"
		});
	}
}
