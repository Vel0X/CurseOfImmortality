// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"

#include "MawOfSothrosStateMachine.h"
#include "NiagaraComponent.h"

AMawOfSothrosPawn::AMawOfSothrosPawn()
{
	StateMachine = CreateDefaultSubobject<UMawOfSothrosStateMachine>("State Machine");

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	PuddleUpperSpawnLocation = CreateDefaultSubobject<USceneComponent>("Upper Spawn Location");
	PuddleUpperSpawnLocation->SetupAttachment(RootComponent);

	PuddleLowerSpawnLocation = CreateDefaultSubobject<USceneComponent>("Lower Spawn Location");
	PuddleLowerSpawnLocation->SetupAttachment(RootComponent);

	VomitUpperJaw = CreateDefaultSubobject<UNiagaraComponent>("Vomit Upper Jaw");
	VomitUpperJaw->SetupAttachment(Mesh, "Upper Jaw");
	
	VomitLowerJaw = CreateDefaultSubobject<UNiagaraComponent>("Vomit Lower Jaw");
	VomitLowerJaw->SetupAttachment(Mesh, "Lower Jaw");
	
	MawSmoke = CreateDefaultSubobject<UNiagaraComponent>("Maw Smoke");
	MawSmoke->SetupAttachment(Mesh);
}
