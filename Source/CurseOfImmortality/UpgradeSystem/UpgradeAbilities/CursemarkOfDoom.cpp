﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CursemarkOfDoom.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/Buffs/CursedBlade.h"

void UCursemarkOfDoom::OnEnemyHit(ABaseCharacter* Enemy)
{
	Super::OnEnemyHit(Enemy);

	//apply the Cursemark Of Doom Buff on the Enemy
	const auto CursedBladeInstance = FPersistentWorldManager::ObjectFactory->GetBuff(CursedBlade);
	Enemy->AddBuff(CursedBladeInstance, AbilityInstance->Caster, Level);
}

void UCursemarkOfDoom::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
	
}
