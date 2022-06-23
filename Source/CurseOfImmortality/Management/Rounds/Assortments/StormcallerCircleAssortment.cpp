// Fill out your copyright notice in the Description page of Project Settings.


#include "StormcallerCircleAssortment.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
 
TArray<ABaseEnemyPawn*> UStormcallerCircleAssortment::SpawnAssortment()
{
	TArray<ABaseEnemyPawn*> Enemies;
	const FVector PlayerPosition = FPersistentWorldManager::PlayerCharacter->GetActorLocation();

	constexpr float MinRadius = 450.0f;
	constexpr float MaxRadius = 500.0f;
	
	FVector CenterPoint = FVector::ZeroVector;
	//Try to find a Center Point
	for (int i = 0; i < 100; ++i)
	{
		const auto Node = FPersistentWorldManager::PathfindingGrid->GetRandomNodeInNavMesh();
		if(!Node->IsWalkable ||Node->GetCombinedHeat() > 20 || Node->SpawnArea)
			continue;

		FVector P = FVector::ZeroVector;
		if(FPersistentWorldManager::PathfindingGrid->GetWorldPositionFromCoordinates(Node->X, Node->Y, P))
		{
			if(FVector::Distance(PlayerPosition, P) > 1000.0f + MaxRadius)
			{
				CenterPoint = P;
				break;
			}
		}
	}
	if(CenterPoint == FVector::ZeroVector)
	{
		return Enemies;
	}

	float CurrentRadians = 0.0f;
	
	for (auto Tuple : EnemiesMap)
	{
		for (int i = 0; i < Tuple.Value; ++i)
		{
			for (int j = 0; j < 100; ++j)
			{
				CurrentRadians += FMath::FRandRange(0.2f, 1.0f);
				const float XPos = FMath::Cos(CurrentRadians);
				const float YPos = FMath::Sin(CurrentRadians);
				
				const float Radius = FMath::RandRange(MinRadius, MaxRadius);
				FVector SpawnPosition = CenterPoint + Radius * FVector(XPos, YPos, 0.0f);
				int X = -1;
				int Y = -1;
				if(FPersistentWorldManager::PathfindingGrid->GetCoordinatesFromWorldPosition( SpawnPosition, X, Y))
				{
					auto Node = FPersistentWorldManager::PathfindingGrid->GetValue(X,Y);
					if(!Node.IsWalkable ||Node.GetCombinedHeat() > 10 || Node.SpawnArea)
						continue;

					FVector ViewDirection = SpawnPosition - CenterPoint;
					ViewDirection.Normalize();
					Enemies.Add(FPersistentWorldManager::ObjectFactory->SpawnEnemy(Tuple.Key, SpawnPosition, ViewDirection.Rotation()));
					break;
				}
			}
		}
	}
	return Enemies;
}
