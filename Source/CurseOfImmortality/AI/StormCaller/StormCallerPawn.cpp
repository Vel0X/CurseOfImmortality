// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/StormCaller/StormCallerPawn.h"

#include "StormCallerStateMachine.h"
#include "CurseOfImmortality/AI/AIBaseClasses/RandomAOEAbility.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

AStormCallerPawn::AStormCallerPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	StateMachine = CreateDefaultSubobject<UStormCallerStateMachine>("StateMachine");

	StormCast = CreateDefaultSubobject<URandomAOEAbility>("Storm Call");
}

bool AStormCallerPawn::GetSpawnPosition(FVector& Position, FRotator& Rotation)
{
	FVector PlayerPosition = FPersistentWorldManager::PlayerCharacter->GetActorLocation();
	for (int i = 0; i < 100; ++i)
	{
		const auto Node = FPersistentWorldManager::PathfindingGrid->GetRandomNodeInNavMesh();
		if(!Node->IsWalkable ||Node->GetCombinedHeat() > 5 || Node->SpawnArea)
			continue;
		
		FVector SpawnPosition = FVector::ZeroVector;
		if(FPersistentWorldManager::PathfindingGrid->GetWorldPositionFromCoordinates(Node->X, Node->Y, SpawnPosition))
		{
			if(FVector::Distance(PlayerPosition, SpawnPosition) > 2000.0f)
			{
				SetActorLocation(SpawnPosition);
				return true;
			}
		}
	}
	return false;
}
