// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"

#include "PersistentWorldManager.h"
#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "CurseOfImmortality/UpgradeSystem/Buffs/Bleed.h"

void ACustomGameMode::SpawnEnemy()
{
	GLog->Log("Spawning Enemy");
}

void ACustomGameMode::AttackManager_PickThreeFromPool() const
{
	const auto AM = FPersistentWorldManager::AttackManager;
	AM->PickThreeFromPool(true);
}

void ACustomGameMode::AttackManager_GetUpgrade(const int Index) const
{
	const auto AM = FPersistentWorldManager::AttackManager;
	AM->GetUpgrade(Index);
}

void ACustomGameMode::AttackManager_PrintCurrentlyActive() const
{
	const auto AM = FPersistentWorldManager::AttackManager;
	AM->PrintCurrentlyActive();
}

void ACustomGameMode::Pathfinding_GetPath(int SX, int SY, int EX, int EY)
{
	const auto PF = FPersistentWorldManager::PathfindingGrid;
	TArray<FPfNode*> Path;
	PF->GetPath(SX, SY, EX, EY, Path, true);
}

void ACustomGameMode::Pathfinding_GetPathWS(float StartX, float StartY, float EndX, float EndY)
{
	const auto PF = FPersistentWorldManager::PathfindingGrid;
	TArray<FVector> Path;

	PF->GetPathWorldSpace(FVector(StartX, StartY, 0.0f), FVector(EndX, EndY, 0.0f), Path, true);
}

void ACustomGameMode::Pathfinding_ToggleWalkable(int X, int Y)
{
	const auto PF = FPersistentWorldManager::PathfindingGrid;
	PF->ToggleWalkable(X, Y);
}

void ACustomGameMode::Pathfinding_GenerateNavmesh()
{
	const auto PF = FPersistentWorldManager::PathfindingGrid;
	PF->GenerateNavmesh();
}

void ACustomGameMode::AddBuffToPlayer(int BuffID) const
{
	const auto AM = FPersistentWorldManager::AttackManager;
	const auto MainChar = FPersistentWorldManager::PlayerCharacter;
	const auto ObjectFactory = FPersistentWorldManager::ObjectFactory;

	/*
	ObjectFactory->GetBuff()
	
	const auto B = AM->PossibleUpgrades->Buffs[BuffID];
	
	MainChar->AddBuff(NewObject<UBaseBuff>(B->StaticClass(), B));
	*/
}

void ACustomGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	FPersistentWorldManager::Clear();
}

