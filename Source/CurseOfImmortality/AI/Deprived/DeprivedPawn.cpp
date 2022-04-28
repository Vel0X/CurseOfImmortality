// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

ADeprivedPawn::ADeprivedPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	AttackSphere = CreateDefaultSubobject<USphereComponent>("AttackSphere");
	AttackSphere->SetupAttachment(RootComponent);

	StateMachine = CreateDefaultSubobject<UDeprivedStateMachine>("StateMachine");

	CurrentJumpAttackCoolDown = 0.f;
	CurrentJumpAttackChargeTime = JumpAttackChargeTime;
	CurrentRecoverDuration = RecoverDuration;
	CurrentNormalAttackDuration = NormalAttackDuration;
}
