// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Inu/InuPawn.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"

AInuPawn::AInuPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	ProjectileLocation = CreateDefaultSubobject<USceneComponent>("ProjectileLocation");
	ProjectileLocation->SetupAttachment(Mesh, "HeadSocket");


	StateMachine = CreateDefaultSubobject<UInuStateMachine>("StateMachine");
}

void AInuPawn::FireProjectile()
{
	FPersistentWorldManager::ObjectFactory->SpawnAbility(
		InuProjectile, ProjectileLocation->GetComponentLocation(), GetActorRotation(), this);
}

void AInuPawn::BeginPlay()
{
	Super::BeginPlay();

	AttackRange = FMath::FRandRange(MinRange, MaxRange);
}
