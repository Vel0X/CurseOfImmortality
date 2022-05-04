// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"

#include "GameController.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"

void ACustomGameMode::SpawnEnemy()
{
	GLog->Log("Spawning Enemy");
}

void ACustomGameMode::AttackManager_PickThreeFromPool() const
{
	const auto AM = static_cast<UGameController*>(GetGameInstance())->GetAttackManager();
	AM->PickThreeFromPool(true);
}

void ACustomGameMode::AttackManager_GetUpgrade(const int Index) const
{
	const auto AM = static_cast<UGameController*>(GetGameInstance())->GetAttackManager();
	AM->GetUpgrade(Index);
}

void ACustomGameMode::AttackManager_PrintCurrentlyActive() const
{
	const auto AM = static_cast<UGameController*>(GetGameInstance())->GetAttackManager();
	AM->PrintCurrentlyActive();
}

void ACustomGameMode::Pathfinding_GetPath(int SX, int SY, int EX, int EY)
{
	const auto PF = static_cast<UGameController*>(GetGameInstance())->GetPathfindingGrid();
	TArray<FPfNode*> Path;
	PF->GetPath(SX, SY, EX, EY, Path, true);
}

void ACustomGameMode::Pathfinding_GetPathWS(float StartX, float StartY, float EndX, float EndY)
{
	const auto PF = static_cast<UGameController*>(GetGameInstance())->GetPathfindingGrid();
	TArray<FVector> Path;

	PF->GetPathWorldSpace(FVector(StartX, StartY, 0.0f), FVector(EndX, EndY, 0.0f), Path, true);
}

void ACustomGameMode::Pathfinding_ToggleWalkable(int X, int Y)
{
	const auto PF = static_cast<UGameController*>(GetGameInstance())->GetPathfindingGrid();
	PF->ToggleWalkable(X, Y);
}

void ACustomGameMode::Pathfinding_GenerateNavmesh()
{
	const auto PF = static_cast<UGameController*>(GetGameInstance())->GetPathfindingGrid();
	PF->GenerateNavmesh();
}

