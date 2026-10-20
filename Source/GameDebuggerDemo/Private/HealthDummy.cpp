#include "HealthDummy.h"

#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

AHealthDummy::AHealthDummy()
{
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(GetCapsuleComponent());
	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (CylinderMesh.Succeeded())
	{
		Body->SetStaticMesh(CylinderMesh.Object);
		// Basic shape cylinder = 100 x 100 x 100 uu, matched to the default capsule (r 34, hh 88)
		Body->SetRelativeScale3D(FVector(0.68f, 0.68f, 1.76f));
	}

	HealthText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthText"));
	HealthText->SetupAttachment(GetCapsuleComponent());
	HealthText->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	HealthText->SetHorizontalAlignment(EHTA_Center);
	HealthText->SetWorldSize(48.f);
	HealthText->SetTextRenderColor(FColor::White);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AHealthDummy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HealthText->SetText(FText::AsNumber(FMath::RoundToInt(HealthComponent->GetHealth())));

	// The text faces the local camera
	if (const APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (PC->PlayerCameraManager)
		{
			const FVector ToCamera = PC->PlayerCameraManager->GetCameraLocation() - HealthText->GetComponentLocation();
			HealthText->SetWorldRotation(FRotator(0.f, ToCamera.ToOrientationRotator().Yaw, 0.f));
		}
	}
}
