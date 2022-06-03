// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleFrenzy.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"


void UBattleFrenzy::OnEnemyHit(ABaseCharacter* Enemy)
{
	Super::OnEnemyHit(Enemy);
	//apply the Adrenaline Rush Buff on the Caster
	const auto AdrenalineRushInstance = FPersistentWorldManager::ObjectFactory->GetBuff(AdrenalineRush);
	AbilityInstance->Caster->AddBuff(AdrenalineRushInstance, AbilityInstance->Caster);
}

void UBattleFrenzy::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
}