// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"

#include "PersistentWorldManager.h"
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

