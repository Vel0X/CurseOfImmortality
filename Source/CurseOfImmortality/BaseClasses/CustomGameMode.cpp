// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"

#include "GameController.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "CurseOfImmortality/UpgradeSystem/Buffs/Bleed.h"

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

void ACustomGameMode::AddBuffToPlayer(int BuffID) const
{
	const auto AM = static_cast<UGameController*>(GetGameInstance())->GetAttackManager();
	const auto MainChar = static_cast<UGameController*>(GetGameInstance())->GetMainChar();
	const auto B = AM->PossibleUpgrades->Buffs[BuffID];
	
	MainChar->AddBuff(NewObject<UBaseBuff>(B->StaticClass(), B));
}

