// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/SeaOfDarkness.h"

#include "Components/SphereComponent.h"

ASeaOfDarkness::ASeaOfDarkness()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Collider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	Collider->SetupAttachment(RootComponent);
}

void ASeaOfDarkness::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (RemainingAbilityLifetime <= 3.f)
	{
		CurrentScale = FMath::FInterpTo(CurrentScale, 0, DeltaSeconds, 1.f);
		FVector Scale(CurrentScale, CurrentScale, 0);
		RootComponent->SetWorldScale3D(Scale);
	}
	else
	{
		CurrentScale = FMath::FInterpTo(CurrentScale, 10, DeltaSeconds, 1.f);
		FVector Scale(CurrentScale, CurrentScale, 0);
		RootComponent->SetWorldScale3D(Scale);
	}
}
