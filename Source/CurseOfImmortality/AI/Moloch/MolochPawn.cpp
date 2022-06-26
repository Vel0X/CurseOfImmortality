// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"

#include "MolochStateMachine.h"

AMolochPawn::AMolochPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	StateMachine = CreateDefaultSubobject<UMolochStateMachine>("StateMachine");

	HeadLocation = CreateDefaultSubobject<USceneComponent>("HeadLocation");
	HeadLocation->SetupAttachment(RootComponent);
}
