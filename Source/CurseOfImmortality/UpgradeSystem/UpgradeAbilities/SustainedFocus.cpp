// Fill out your copyright notice in the Description page of Project Settings.


#include "SustainedFocus.h"

#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"

void USustainedFocus::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
	switch(UpgradeLevel)
	{
	case 1:
		DurationModifier = 1.25f;
		break;
	case 2:
		DurationModifier = 1.5f;
		break;
	case 3:
		DurationModifier = 1.75f;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Invalid Upgradelevel for SustainedFocus"));
		break;
	}
}

void USustainedFocus::OnAbilityStart()
{
	Super::OnAbilityStart();

	AbilityInstance->AbilityLifetime *= DurationModifier;
	AbilityInstance->ResetLifetime();

}
