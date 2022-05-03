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

