// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Inu/InuPawn.h"

AInuPawn::AInuPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	StateMachine = CreateDefaultSubobject<UInuStateMachine>("StateMachine");

	AttackRange = FMath::FRandRange(MinRange, MaxRange);
}

void AInuPawn::FireProjectile()
{
}
