using UnrealBuildTool;

public class GameDebuggerDemoTarget : TargetRules
{
	public GameDebuggerDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("GameDebuggerDemo");
	}
}
