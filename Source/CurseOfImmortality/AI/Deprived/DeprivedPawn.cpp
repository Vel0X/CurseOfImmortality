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

bool ADeprivedPawn::IsRecover() const
{
	return Recover;
}

void ADeprivedPawn::SetRecover(const bool bStandUp)
{
	Recover = bStandUp;
}

bool ADeprivedPawn::IsIdle() const
{
	return Idle;
}

void ADeprivedPawn::SetIdle(const bool bIdle)
{
	Idle = bIdle;
}

bool ADeprivedPawn::IsRunning() const
{
	return Running;
}

void ADeprivedPawn::SetRunning(const bool bMoving)
{
	Running = bMoving;
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
