// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"

#include "CurseOfImmortality/Enemies/EnemySpecification.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"


bool ABaseEnemyPawn::GetSpawnPosition(FVector& Position, FRotator& Rotation)
{
	USceneComponent* Gate = FPersistentWorldManager::Arena->GetRandomGate();
	const FVector GatePosition = Gate->GetComponentLocation();
	Position = GatePosition;
	SetActorLocation(Position);
	return true;
}


void ABaseEnemyPawn::Init(const UEnemySpecification* Specification)
{
	PowerLevel = Specification->PowerLevel;
}

