// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"

#include "MawOfSothrosStateMachine.h"
#include "NiagaraComponent.h"

AMawOfSothrosPawn::AMawOfSothrosPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	StateMachine = CreateDefaultSubobject<UMawOfSothrosStateMachine>("StateMachine");
	VomitUpperJaw = CreateDefaultSubobject<UNiagaraComponent>("Vomit Upper Jaw");
	VomitUpperJaw->SetupAttachment(Mesh, "UpperJaw");
	VomitLowerJaw = CreateDefaultSubobject<UNiagaraComponent>("Vomit Lower Jaw");
	VomitLowerJaw->SetupAttachment(Mesh, "LowerJaw");
	MawSmoke = CreateDefaultSubobject<UNiagaraComponent>("Maw Smoke");
	MawSmoke->SetupAttachment(Mesh);
}
