// Fill out your copyright notice in the Description page of Project Settings.


#include "StormcallerCircleAssortment.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

TArray<ABaseEnemyPawn*> UStormcallerCircleAssortment::SpawnAssortment()
{

	//TODO: determine a point in the arena, that is at least MaxRadius away from the walls of the arena and also far away from the player
	const FVector Point = FVector(0,0,0);
	TArray<ABaseEnemyPawn*> Enemies;

	float CurrentRadians = 0.0f;
	
	for (auto Tuple : EnemiesMap)
	{
		for (int i = 0; i < Tuple.Value; ++i)
		{
			constexpr int MinRadius = 900.0f;
			constexpr int MaxRadius = 1200.0f;
			
			CurrentRadians += FMath::FRandRange(0.2f, 1.0f);
			const float XPos = FMath::Cos(CurrentRadians);
			const float YPos = FMath::Sin(CurrentRadians);

			const float Radius = FMath::RandRange(MinRadius, MaxRadius);

			//TODO: check if the SpawnPosition is free. If not, continue to iterate
			FVector SpawnPosition = Point + Radius * FVector(XPos, YPos, 0.0f);
			FVector ViewDirection = SpawnPosition - Point;
			SpawnPosition.Z += 100.0f;
			ViewDirection.Normalize();
			Enemies.Add(FPersistentWorldManager::ObjectFactory->SpawnEnemy(Tuple.Key, SpawnPosition, ViewDirection.Rotation()));
		}
	}
	return Enemies;}
