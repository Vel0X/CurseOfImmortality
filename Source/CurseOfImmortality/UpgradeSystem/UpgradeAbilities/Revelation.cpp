// Fill out your copyright notice in the Description page of Project Settings.


#include "Revelation.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void URevelation::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
}

void URevelation::OnAbilityStart()
{
	Super::OnAbilityStart();

	//apply the Cursemark Of Doom Buff on the Enemy
	const auto SoulFlayerInstance = FPersistentWorldManager::ObjectFactory->GetBuff(SoulFlayer);
	AbilityInstance->Caster->AddBuff(SoulFlayerInstance, AbilityInstance->Caster, Level);
}
