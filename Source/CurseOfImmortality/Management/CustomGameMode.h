// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CustomGameMode.generated.h"

class ABaseEnemyPawn;
class UTrapManagerCopmonent;
class AArena;
class ASoundManager;
class ARoundsManager;
class APathfindingGrid;
class AObjectFactory;
class APlayerCharacter;
class UAttackManager;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ACustomGameMode final : public AGameMode
{
	GENERATED_BODY()
public:
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowUpgradeMenu();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowDeathScreen();

/////////////////////////////////////////////////////////////////////
///-------------------WORLD MANAGER INTERFACE---------------------///
/////////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable)
	UAttackManager* AttackManager();
	UFUNCTION(BlueprintCallable)
	APlayerCharacter* PlayerCharacter();
	UFUNCTION(BlueprintCallable)
	AObjectFactory* ObjectFactory();
	UFUNCTION(BlueprintCallable)
	APathfindingGrid* PathfindingGrid();
	UFUNCTION(BlueprintCallable)
	ARoundsManager* RoundsManager();
	UFUNCTION(BlueprintCallable)
	ASoundManager* SoundManager();
	UFUNCTION(BlueprintCallable)
	AArena* Arena();
	UFUNCTION(BlueprintCallable)
	UTrapManagerCopmonent* TrapManager();
	UFUNCTION(BlueprintCallable)
	ACustomGameMode* GameMode();
	UFUNCTION(BlueprintCallable)
	ABaseEnemyPawn* Maw();
/////////////////////////////////////////////////////////////////////
///-------------------------COMMANDS------------------------------///
/////////////////////////////////////////////////////////////////////

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
	static void AddBuffToPlayer(FString Key);

	UFUNCTION(Exec, Category = ExecFunctions)
	static void SetLogLevel(FString Key, bool Log);

	UFUNCTION(Exec, Category = ExecFunctions)
	static void SetControlFlag(FString Flag, bool Value);
};
