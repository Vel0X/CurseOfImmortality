// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"


ABaseEnemyPawn::ABaseEnemyPawn()
{
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>("Collision Capsule");
	SetRootComponent(CollisionCapsule);
}

UCapsuleComponent* ABaseEnemyPawn::GetCollisionCapsule() const
{
	return CollisionCapsule;
}
