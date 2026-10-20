#include "HealthDamageZone.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AHealthDamageZone::AHealthDamageZone()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetBoxExtent(FVector(200.f, 200.f, 100.f));
	Box->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Box->SetGenerateOverlapEvents(true);
	Box->ShapeColor = FColor::Red;
	Box->SetHiddenInGame(false);
	Box->SetLineThickness(4.f);
}

void AHealthDamageZone::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(DamageTimer, this, &AHealthDamageZone::ApplyZoneDamage, TickInterval, true);
	}
}

void AHealthDamageZone::ApplyZoneDamage()
{
	TArray<AActor*> Overlapping;
	Box->GetOverlappingActors(Overlapping, APawn::StaticClass());

	for (AActor* Actor : Overlapping)
	{
		UGameplayStatics::ApplyDamage(Actor, DamagePerTick, nullptr, this, nullptr);
	}
}
