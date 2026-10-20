#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthDamageZone.generated.h"

class UBoxComponent;

/**
 * Applies damage at a fixed interval to every Pawn overlapping the box.
 */
UCLASS()
class GAMEDEBUGGERDEMO_API AHealthDamageZone : public AActor
{
	GENERATED_BODY()

public:
	AHealthDamageZone();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage Zone")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Zone", meta = (ClampMin = "0"))
	float DamagePerTick = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Zone", meta = (ClampMin = "0.1"))
	float TickInterval = 1.f;

private:
	void ApplyZoneDamage();

	FTimerHandle DamageTimer;
};
