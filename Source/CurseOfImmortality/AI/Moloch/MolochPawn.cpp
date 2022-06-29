// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"

#include "MolochStateMachine.h"
#include "Components/CapsuleComponent.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageComponent.h"

AMolochPawn::AMolochPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	StateMachine = CreateDefaultSubobject<UMolochStateMachine>("StateMachine");

	HeadLocation = CreateDefaultSubobject<USceneComponent>("HeadLocation");
	HeadLocation->SetupAttachment(RootComponent);
	BackLocation = CreateDefaultSubobject<USceneComponent>("BackLocation");
	BackLocation->SetupAttachment(RootComponent);

	HeadAttack = CreateDefaultSubobject<UCapsuleComponent>("HeadAttack");
	HeadAttack->SetupAttachment(Mesh, "HeadSocket");
	BackAttack = CreateDefaultSubobject<UCapsuleComponent>("BackAttack");
	BackAttack->SetupAttachment(Mesh, "BackAttackSocket");

	BodyCollision = CreateDefaultSubobject<UCapsuleComponent>("BodyCollision");
	BodyCollision->SetupAttachment(RootComponent);
}

void AMolochPawn::ToggleChargeAttack()
{
	DamageComponent->ResetAllHitCharacters();
	HeadAttack->SetGenerateOverlapEvents(!HeadAttack->GetGenerateOverlapEvents());
}

void AMolochPawn::ToggleKick()
{
	DamageComponent->ResetAllHitCharacters();
	BackAttack->SetGenerateOverlapEvents(!BackAttack->GetGenerateOverlapEvents());
}
