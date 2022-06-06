// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"

#include "PersistentWorldManager.h"
#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "CurseOfImmortality/UpgradeSystem/Buffs/Bleed.h"


void ACustomGameMode::SpawnEnemy(int Index, const float X, const float Y, const float Z)
{
	const FVector Location = FVector(X, Y, Z);
	FPersistentWorldManager::ObjectFactory->SpawnEnemy(static_cast<EEnemy>(Index), Location, FRotator::ZeroRotator);
}

void ACustomGameMode::SpawnEnemyCustomSpawnBehaviour(int Index)
{
	FPersistentWorldManager::ObjectFactory->SpawnEnemyCustomSpawnBehaviour(static_cast<EEnemy>(Index));
}

void ACustomGameMode::SpawnEnemyByName(const FString Index, const float X, const float Y, const float Z)
{
	const FVector Location = FVector(X, Y, Z);

	EEnemy E = {};
	const FString IndexToLower = Index.ToLower();
	if (IndexToLower == "deprived")
		E = Deprived;
	else if (IndexToLower == "stormcaller")
		E = Stormcaller;
	else if (IndexToLower == "mawofsothros")
		E = MawOfSothros;

	FPersistentWorldManager::ObjectFactory->SpawnEnemy(E, Location, FRotator::ZeroRotator);
}

void ACustomGameMode::SpawnEnemyByNameCustomSpawnBehaviour(FString Index)
{
	EEnemy E = {};
	const FString IndexToLower = Index.ToLower();
	if (IndexToLower == "deprived")
		E = Deprived;
	else if (IndexToLower == "stormcaller")
		E = Stormcaller;
	else if (IndexToLower == "mawofsothros")
		E = MawOfSothros;

	FPersistentWorldManager::ObjectFactory->SpawnEnemyCustomSpawnBehaviour(E);
}

void ACustomGameMode::StartRound(const int Index)
{
	if (FPersistentWorldManager::RoundsManager != nullptr)
	{
		FPersistentWorldManager::RoundsManager->StartRound(Index);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("RoundManager was NULL"));
	}
}

void ACustomGameMode::AttackManager_PickThreeFromPool()
{
	const auto AM = FPersistentWorldManager::AttackManager;
	AM->PickThreeFromPool(true);
}

void ACustomGameMode::AttackManager_GetUpgrade(const int Index)
{
	const auto AM = FPersistentWorldManager::AttackManager;
	AM->GetUpgrade(Index);
}

void ACustomGameMode::AttackManager_PrintCurrentlyActive()
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

void ACustomGameMode::AddBuffToPlayer(FString Key)
{
	const auto MainChar = FPersistentWorldManager::PlayerCharacter;
	const auto ObjectFactory = FPersistentWorldManager::ObjectFactory;

	EBuff Buff = {};
	const FString IndexToLower = Key.ToLower();
	if (IndexToLower == "soulflayer")
		Buff = SoulFlayer;
	else if (IndexToLower == "bleed")
		Buff = Bleed;
	else if (IndexToLower == "rejuvenation")
		Buff = Rejuvenation;
	UBaseBuff* BuffInstance = ObjectFactory->GetBuff(Buff);
	BuffInstance->SetupBuff(ObjectFactory->GetSpecification(Buff));
	MainChar->AddBuff(BuffInstance, nullptr, 1);
}

void ACustomGameMode::SetLogLevel(const FString Key, const bool Log)
{
	FPersistentWorldManager::SetLogLevel(Key, Log);
}

void ACustomGameMode::SetControlFlag(const FString Flag, const bool Value)
{
	FPersistentWorldManager::SetControlFlag(Flag, Value);
}

void ACustomGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//Set Flags from Config
}

void ACustomGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	FPersistentWorldManager::Clear();
}
