#include "HealthComponent.h"

#include "GameFramework/Actor.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
	}
}

void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                           AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f)
	{
		return;
	}

	LastDamageCauser = DamageCauser;

	const float OldHealth = Health;
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(Health, Health - OldHealth);

	if (Health <= 0.f)
	{
		OnDeath.Broadcast();
		Health = MaxHealth;
		OnHealthChanged.Broadcast(Health, MaxHealth);
	}
}
