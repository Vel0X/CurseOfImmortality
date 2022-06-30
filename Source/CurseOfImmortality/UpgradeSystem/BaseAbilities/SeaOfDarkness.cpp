// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/SeaOfDarkness.h"

#include "Components/SphereComponent.h"
#include "CurseOfImmortality/AI/Inu/InuPawn.h"
#include "CurseOfImmortality/Management/ObjectFactory.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

ASeaOfDarkness::ASeaOfDarkness()
{
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SetRootComponent(Collider);
	// RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void ASeaOfDarkness::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Rand <= 0.5f)
	{
		if (!InuSpawned)
		{
			if (SpawnDelay <= 0)
			{
				FVector Dir = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() -
					GetActorLocation();
				Dir.Z = 0;
				const FRotator InuRotation = Dir.Rotation();
				InuSpawned = true;
				const AObjectFactory* ObjectFactory = FPersistentWorldManager::ObjectFactory;
				if (!ObjectFactory) { return; }
				AInuPawn* InuPawn = Cast<AInuPawn>(
					ObjectFactory->SpawnEnemy(Inu, Collider->GetComponentLocation(), InuRotation));
				if (!InuPawn) { return; }
				InuPawn->SetActorLocation(Collider->GetComponentLocation());
				InuPawn->SpawnedByMaw = true;
			}
			SpawnDelay -= DeltaSeconds;
		}
	}

	if (RemainingAbilityLifetime <= 3.f)
	{
		CurrentScale = FMath::FInterpTo(CurrentScale, 0, DeltaSeconds, 1.f);
		FVector Scale(CurrentScale);
		RootComponent->SetWorldScale3D(Scale);
	}
	else
	{
		CurrentScale = FMath::FInterpTo(CurrentScale, 10, DeltaSeconds, 1.f);
		FVector Scale(CurrentScale);
		RootComponent->SetWorldScale3D(Scale);
	}
}

void ASeaOfDarkness::BeginPlay()
{
	Super::BeginPlay();

	Rand = FMath::FRandRange(0.f, 1.f);
}
