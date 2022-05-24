// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ACustomGameMode final : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec, Category = ExecFunctions)
	static void SpawnEnemy(int Index, float X, float Y, float Z);

	UFUNCTION(Exec, Category = ExecFunctions)
	static void SpawnEnemyCustomSpawnBehaviour(int Index);

	UFUNCTION(Exec, Category = ExecFunctions)
	static void SpawnEnemyByName(FString Index, float X, float Y, float Z);

	UFUNCTION(Exec, Category = ExecFunctions)
	static void SpawnEnemyByNameCustomSpawnBehaviour(FString Index);

	UFUNCTION(Exec, Category = ExecFunctions)
	static void StartRound(const int Index);
	
	UFUNCTION(Exec, Category = ExecFunctions)
	static void AttackManager_PickThreeFromPool();

	UFUNCTION(Exec, Category = ExecFunctions)
	static void AttackManager_GetUpgrade(int Index);

	UFUNCTION(Exec, Category = ExecFunctions)
	static void AttackManager_PrintCurrentlyActive();

	UFUNCTION(Exec, Category= ExecFunctions)
	static void Pathfinding_GetPath(int SX, int SY, int EX, int EY);

	UFUNCTION(Exec, Category= ExecFunctions)
	static void Pathfinding_GetPathWS(float StartX, float StartY, float EndX, float EndY);
	
	UFUNCTION(Exec, Category= ExecFunctions)
	static void Pathfinding_ToggleWalkable(int X, int Y);
	
	UFUNCTION(Exec, Category= ExecFunctions)
	static void Pathfinding_GenerateNavmesh();

	UFUNCTION(Exec, Category = ExecFunctions)
	static void AddBuffToPlayer(int BuffID);


	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
