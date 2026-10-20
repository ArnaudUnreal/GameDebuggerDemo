#include "HealthSystemModule.h"

#include "Modules/ModuleManager.h"

#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebugger.h"
#include "GameplayDebuggerCategory_Health.h"
#endif

void FHealthSystemModule::StartupModule()
{
#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebugger = IGameplayDebugger::Get();
	GameplayDebugger.RegisterCategory("Health",
		IGameplayDebugger::FOnGetCategory::CreateStatic(&FGameplayDebuggerCategory_Health::MakeInstance),
		EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 6);
	GameplayDebugger.NotifyCategoriesChanged();
#endif
}

void FHealthSystemModule::ShutdownModule()
{
#if WITH_GAMEPLAY_DEBUGGER
	if (IGameplayDebugger::IsAvailable())
	{
		IGameplayDebugger& GameplayDebugger = IGameplayDebugger::Get();
		GameplayDebugger.UnregisterCategory("Health");
		GameplayDebugger.NotifyCategoriesChanged();
	}
#endif
}

IMPLEMENT_MODULE(FHealthSystemModule, HealthSystem)
