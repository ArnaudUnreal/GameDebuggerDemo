#include "GameplayDebuggerCategory_Health.h"

#if WITH_GAMEPLAY_DEBUGGER

#include "HealthComponent.h"
#include "GameFramework/Actor.h"

namespace HealthDebugger
{
static const TCHAR* GetNetModeName(const ENetMode NetMode)
{
	switch (NetMode)
	{
	case NM_DedicatedServer: return TEXT("Dedicated Server");
	case NM_ListenServer:    return TEXT("Listen Server");
	case NM_Client:          return TEXT("Client");
	default:                 return TEXT("Standalone");
	}
}
}

FGameplayDebuggerCategory_Health::FGameplayDebuggerCategory_Health()
{
	bShowOnlyWithDebugActor = true;
}

void FGameplayDebuggerCategory_Health::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	const UHealthComponent* HealthComponent = DebugActor ? DebugActor->FindComponentByClass<UHealthComponent>() : nullptr;
	if (!HealthComponent)
	{
		AddTextLine(TEXT("{red}No HealthComponent"));
		return;
	}

	// --- Cycle 1 : text ---
	AddTextLine(FString::Printf(TEXT("{yellow}Health: {white}%.0f / %.0f"), HealthComponent->GetHealth(), HealthComponent->GetMaxHealth()));

	const AActor* Causer = HealthComponent->GetLastDamageCauser();
	AddTextLine(FString::Printf(TEXT("{yellow}Last damage causer: {white}%s"), *GetNameSafe(Causer)));

	// --- Cycle 2 : shapes ---
	const float Ratio = HealthComponent->GetHealth() / HealthComponent->GetMaxHealth();
	const FColor HealthColor = FLinearColor::LerpUsingHSV(FLinearColor::Red, FLinearColor::Green, Ratio).ToFColor(true);

	AddShape(FGameplayDebuggerShape::MakeCylinder(DebugActor->GetActorLocation(), 60.f, 100.f, HealthColor));

	if (Causer)
	{
		AddShape(FGameplayDebuggerShape::MakeSegment(DebugActor->GetActorLocation(), Causer->GetActorLocation(), 3.f, FColor::Orange));
	}

	// --- Cycle 3 : where is CollectData running? ---
	AddTextLine(FString::Printf(TEXT("{yellow}Collected on: {white}%s"), HealthDebugger::GetNetModeName(DebugActor->GetNetMode())));
}

TSharedRef<FGameplayDebuggerCategory> FGameplayDebuggerCategory_Health::MakeInstance()
{
	return MakeShareable(new FGameplayDebuggerCategory_Health());
}

#endif // WITH_GAMEPLAY_DEBUGGER
