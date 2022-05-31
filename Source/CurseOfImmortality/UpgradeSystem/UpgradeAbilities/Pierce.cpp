// Fill out your copyright notice in the Description page of Project Settings.


#include "Pierce.h"

#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"

void UPierce::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
	switch(UpgradeLevel)
	{
	case 1:
		PiercesLeft = 1;
		break;
	case 2:
		PiercesLeft = 3;
		break;
	case 3:
		PiercesLeft = 5;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Invalid Upgradelevel for Pierce"));
		break;
	}
}

void UPierce::OnEnemyHit(ABaseCharacter* Enemy)
{
	Super::OnEnemyHit(Enemy);

	if(HitCharacters.Contains(Enemy))
		return;
	
	if(PiercesLeft > 0)
	{
		AbilityInstance->DestroyOnEnemyHit = false;
		HitCharacters.Add(Enemy);
		PiercesLeft--;
	}
	else
	{
		AbilityInstance->DestroyOnEnemyHit = true;
	}
	
}
