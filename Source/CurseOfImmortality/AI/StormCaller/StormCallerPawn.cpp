// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/StormCaller/StormCallerPawn.h"

#include "StormCallerStateMachine.h"
#include "CurseOfImmortality/AI/AIBaseClasses/RandomAOEAbility.h"

AStormCallerPawn::AStormCallerPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	StateMachine = CreateDefaultSubobject<UStormCallerStateMachine>("StateMachine");

	StormCast = CreateDefaultSubobject<URandomAOEAbility>("Storm Call");
}

void AStormCallerPawn::OnDeath()
{
	Dead = true;
	StateMachine->DestroyComponent();
	CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
}
