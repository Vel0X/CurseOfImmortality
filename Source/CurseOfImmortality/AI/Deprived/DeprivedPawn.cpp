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
}

USphereComponent* ADeprivedPawn::GetAttackSphere() const
{
	return AttackSphere;
}

bool ADeprivedPawn::IsHitPlayer() const
{
	return HitPlayer;
}

void ADeprivedPawn::SetHitPlayer(const bool bHitPlayer)
{
	HitPlayer = bHitPlayer;
}

bool ADeprivedPawn::IsStandUp() const
{
	return StandUp;
}

void ADeprivedPawn::SetStandUp(const bool bStandUp)
{
	StandUp = bStandUp;
}

bool ADeprivedPawn::IsIdle() const
{
	return Idle;
}

void ADeprivedPawn::SetIdle(const bool bIdle)
{
	Idle = bIdle;
}

bool ADeprivedPawn::IsMoving() const
{
	return Moving;
}

void ADeprivedPawn::SetMoving(const bool bMoving)
{
	Moving = bMoving;
}

bool ADeprivedPawn::IsJump() const
{
	return Jump;
}

void ADeprivedPawn::SetJump(const bool bJump)
{
	Jump = bJump;
}

bool ADeprivedPawn::IsStunned() const
{
	return Stunned;
}

void ADeprivedPawn::SetStunned(const bool bStunned)
{
	Stunned = bStunned;
}
