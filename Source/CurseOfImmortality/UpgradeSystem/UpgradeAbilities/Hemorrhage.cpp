// Fill out your copyright notice in the Description page of Project Settings.


#include "Hemorrhage.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UHemorrhage::OnEnemyHit(ABaseCharacter* Enemy)
{
	Super::OnEnemyHit(Enemy);
	//apply the Cursemark Of Doom Buff on the Enemy
	const auto BleedInstance = FPersistentWorldManager::ObjectFactory->GetBuff(Bleed);
	Enemy->AddBuff(BleedInstance, AbilityInstance->Caster);
}
