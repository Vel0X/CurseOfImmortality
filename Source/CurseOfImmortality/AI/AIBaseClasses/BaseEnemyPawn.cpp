// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"


bool ABaseEnemyPawn::GetSpawnPosition(FVector& Position, FRotator& Rotation)
{
	USceneComponent* Gate = FPersistentWorldManager::Arena->GetRandomGate();
	FVector GatePosition = Gate->GetComponentLocation();
	GatePosition.Z += 100.0f;
	Position = GatePosition;
	UE_LOG(LogTemp, Warning, TEXT("Spawning At Pos %f, %f, %f"), Position.X, Position.Y, Position.Z);
	SetActorLocation(Position);
	return true;
}
