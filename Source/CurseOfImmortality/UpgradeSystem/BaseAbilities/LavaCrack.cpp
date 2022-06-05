// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/LavaCrack.h"

#include "Components/SphereComponent.h"

ALavaCrack::ALavaCrack()
{
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SetRootComponent(Collider);
	// RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void ALavaCrack::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// if (RemainingAbilityLifetime <= 3.f)
	// {
	// 	CurrentScale = FMath::FInterpTo(CurrentScale, 0, DeltaSeconds, 1.f);
	// 	FVector Scale(CurrentScale);
	// 	RootComponent->SetWorldScale3D(Scale);
	// }
	// else
	// {
	// 	CurrentScale = FMath::FInterpTo(CurrentScale, 10, DeltaSeconds, 1.f);
	// 	FVector Scale(CurrentScale);
	// 	RootComponent->SetWorldScale3D(Scale);
	// }
}
