using UnrealBuildTool;

public class GameDebuggerDemoEditorTarget : TargetRules
{
	public GameDebuggerDemoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("GameDebuggerDemo");
	}
}
