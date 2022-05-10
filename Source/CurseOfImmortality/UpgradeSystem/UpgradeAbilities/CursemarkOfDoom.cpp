// Fill out your copyright notice in the Description page of Project Settings.


#include "CursemarkOfDoom.h"
#include "CurseOfImmortality/UpgradeSystem/GameDummy/Char.h"
#include "CurseOfImmortality/UpgradeSystem/Buffs/CursedBlade.h"

void UCursemarkOfDoom::OnEnemyHit(AChar* Enemy)
{
	Super::OnEnemyHit(Enemy);

	//apply the Cursemark Of Doom Buff on the Enemy
	UE_LOG(LogTemp, Warning, TEXT("Add Cursed Blade Instance on Enemy Hit"));
	const auto CursedBladeInstance = NewObject<UCursedBlade>();
	Enemy->AddBuff(CursedBladeInstance);
}

void UCursemarkOfDoom::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
}
