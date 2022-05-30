// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"

#include "MawOfSothrosStateMachine.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"

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

	UpperBodyCollision = CreateDefaultSubobject<UCapsuleComponent>("Upper Body Collision");
	UpperBodyCollision->SetupAttachment(Mesh, "UpperBodyCollisionSocket");
	UpperLeftArmCollision = CreateDefaultSubobject<UCapsuleComponent>("Upper Left Arm Collision");
	UpperLeftArmCollision->SetupAttachment(Mesh, "UpperLeftArmCollisionSocket");
	LowerLeftArmCollision = CreateDefaultSubobject<UCapsuleComponent>("Lower Left Arm Collision");
	LowerLeftArmCollision->SetupAttachment(Mesh, "LowerLeftArmCollisionSocket");
	UpperRightArmCollision = CreateDefaultSubobject<UCapsuleComponent>("Upper Right Arm Collision");
	UpperRightArmCollision->SetupAttachment(Mesh, "UpperRightArmCollisionSocket");
	LowerRightArmCollision = CreateDefaultSubobject<UCapsuleComponent>("Lower Right Arm Collision");
	LowerRightArmCollision->SetupAttachment(Mesh, "LowerRightArmCollisionSocket");
	HeadCollision = CreateDefaultSubobject<USphereComponent>("Head Collision");
	HeadCollision->SetupAttachment(Mesh, "HeadCollisionSocket");
	TailDamageSphere = CreateDefaultSubobject<USphereComponent>("TailDamageSphere");
	TailDamageSphere->SetupAttachment(Mesh, "TailDamageSphere");
	SmokeDamageSphere = CreateDefaultSubobject<USphereComponent>("SmokeDamageSphere");
	SmokeDamageSphere->SetupAttachment(Mesh);
	ChargeAttackDamageCapsule = CreateDefaultSubobject<UCapsuleComponent>("ChargeAttackDamageCapsule");
	ChargeAttackDamageCapsule->SetupAttachment(Mesh);
}

void AMawOfSothrosPawn::ActivateVomit()
{
	VomitLowerJaw->Activate();
	VomitUpperJaw->Activate();

	SpawnPuddle = true;
}

void AMawOfSothrosPawn::DeactivateVomit()
{
	VomitLowerJaw->Deactivate();
	VomitUpperJaw->Deactivate();

	SpawnPuddle = false;
}
