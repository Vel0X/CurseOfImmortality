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

	HeadAttack = CreateDefaultSubobject<UCapsuleComponent>("HeadAttack");
	HeadAttack->SetupAttachment(Mesh, "HeadSocket");

	BodyCollision = CreateDefaultSubobject<UCapsuleComponent>("BodyCollision");
	BodyCollision->SetupAttachment(RootComponent);
}

void AMolochPawn::ToggleChargeAttack()
{
	HeadAttack->SetGenerateOverlapEvents(!HeadAttack->GetGenerateOverlapEvents());

	UE_LOG(LogTemp, Error, TEXT("Toggle"));

	DamageComponent->ResetAllHitCharacters();
}
