// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ACustomGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec, Category = ExecFunctions)
	void SpawnEnemy();

	UFUNCTION(Exec, Category = ExecFunctions)
	void AttackManager_PickThreeFromPool() const;

	UFUNCTION(Exec, Category = ExecFunctions)
	void AttackManager_GetUpgrade(int Index) const;

	UFUNCTION(Exec, Category = ExecFunctions)
	void AttackManager_PrintCurrentlyActive() const;

	UFUNCTION(Exec, Category= ExecFunctions)
	void Pathfinding_GetPath(int SX, int SY, int EX, int EY);

	UFUNCTION(Exec, Category= ExecFunctions)
	void Pathfinding_GetPathWS(float StartX, float StartY, float EndX, float EndY);
	
	UFUNCTION(Exec, Category= ExecFunctions)
	void Pathfinding_ToggleWalkable(int X, int Y);
	
	UFUNCTION(Exec, Category= ExecFunctions)
	void Pathfinding_GenerateNavmesh();

	UFUNCTION(Exec, Category = ExecFunctions)
	void AddBuffToPlayer(int BuffID) const;


	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
