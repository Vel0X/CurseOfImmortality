// Fill out your copyright notice in the Description page of Project Settings.


#include "Pierce.h"

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
		UE_LOG(LogTemp, Error, TEXT("Invalid Upgradelevel for Seal of Congruence"));
		break;
	}
}

void UPierce::OnEnemyHit()
{
	Super::OnEnemyHit();
	
	ABaseAbility* Owner = static_cast<ABaseAbility*>(GetOwner());
	if(PiercesLeft > 0)
	{
		Owner->DestroyOnEnemyHit = false;
		PiercesLeft--;
	}
	else
	{
		Owner->DestroyOnEnemyHit = true;
	}
	
}
