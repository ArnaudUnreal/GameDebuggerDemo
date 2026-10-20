#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthDummy.generated.h"

class UHealthComponent;
class UStaticMeshComponent;
class UTextRenderComponent;

/**
 * Training dummy: a Character with a UHealthComponent.
 * The TextRender displays the current health above the dummy.
 */
UCLASS()
class GAMEDEBUGGERDEMO_API AHealthDummy : public ACharacter
{
	GENERATED_BODY()

public:
	AHealthDummy();

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dummy")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dummy")
	TObjectPtr<UTextRenderComponent> HealthText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dummy")
	TObjectPtr<UHealthComponent> HealthComponent;
};
