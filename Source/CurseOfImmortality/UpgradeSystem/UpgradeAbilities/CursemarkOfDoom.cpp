// Fill out your copyright notice in the Description page of Project Settings.


#include "CursemarkOfDoom.h"

#include "CurseOfImmortality/UpgradeSystem/Buffs/Bleed.h"

void UCursemarkOfDoom::OnEnemyHit(AChar* Enemy)
{
	Super::OnEnemyHit(Enemy);

	//apply the Cursemark Of Doom Buff on the Enemy
	UE_LOG(LogTemp, Warning, TEXT("yyyyy"));
	const auto BleedInstance = NewObject<UBleed>();
	Enemy->AddBuff(BleedInstance);
}

void UCursemarkOfDoom::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
}
