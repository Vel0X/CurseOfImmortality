// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/TrapProjectile.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

ATrapProjectile::ATrapProjectile()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	Trail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail"));
	Trail->SetupAttachment(ProjectileMesh);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(ProjectileMesh);
}

void ATrapProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector DeltaLocation = GetActorForwardVector() * Speed * DeltaSeconds * 100.0f;
	AddActorWorldOffset(DeltaLocation, false);
}
