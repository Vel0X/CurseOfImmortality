// Fill out your copyright notice in the Description page of Project Settings.


#include "Fireball.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

AFireball::AFireball()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	Trail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail"));
	Trail->SetupAttachment(ProjectileMesh);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(ProjectileMesh);
}

void AFireball::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const FVector DeltaLocation = GetActorForwardVector() * Speed * DeltaSeconds * 100.0f;
	AddActorWorldOffset(DeltaLocation, false);
}
