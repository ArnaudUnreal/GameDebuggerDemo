#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UDamageType;
class AController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

/**
 * Health driven by the owner's OnTakeAnyDamage.
 * At 0, the owner is "respawned": health goes back to MaxHealth.
 */
UCLASS(ClassGroup = (Gameplay), meta = (BlueprintSpawnableComponent))
class HEALTHSYSTEM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintPure, Category = "Health")
	AActor* GetLastDamageCauser() const { return LastDamageCauser.Get(); }

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (ClampMin = "1"))
	float MaxHealth = 100.f;

private:
	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                         AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(VisibleInstanceOnly, Category = "Health")
	float Health = 0.f;

	TWeakObjectPtr<AActor> LastDamageCauser;
};
