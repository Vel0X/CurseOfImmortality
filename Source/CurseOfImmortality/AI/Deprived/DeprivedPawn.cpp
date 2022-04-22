// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

ADeprivedPawn::ADeprivedPawn()
{
	StateMachine = CreateDefaultSubobject<UDeprivedStateMachine>("StateMachine");

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>("CollisionCapsule");
	SetRootComponent(CollisionCapsule);

	AttackSphere = CreateDefaultSubobject<USphereComponent>("AttackSphere");
	AttackSphere->SetupAttachment(RootComponent);
}

USphereComponent* ADeprivedPawn::GetAttackSphere() const
{
	return AttackSphere;
}

UCapsuleComponent* ADeprivedPawn::GetCollisionCapsule() const
{
	return CollisionCapsule;
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