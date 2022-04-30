// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneReplicatorTurret.h"

AArcaneReplicatorTurret::AArcaneReplicatorTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void AArcaneReplicatorTurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const FVector Offset = DeltaSeconds * 100.0f * Speed * GetActorForwardVector();
	AddActorWorldOffset(Offset, false);
}
