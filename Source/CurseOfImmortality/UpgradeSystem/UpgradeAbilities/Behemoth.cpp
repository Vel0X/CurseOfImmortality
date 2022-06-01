// Fill out your copyright notice in the Description page of Project Settings.


#include "Behemoth.h"

#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"


void UBehemoth::OnAbilityStart()
{
	Super::OnAbilityStart();

	if(Proc == false)
	{
		AbilityInstance->RelativeSize *= SizeIncrease;
		Proc = true;
	}

}

void UBehemoth::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
	switch(UpgradeLevel)
	{
	case 1:
		SizeIncrease = 1.25f;
		break;
	case 2:
		SizeIncrease = 1.5f;
		break;
	case 3:
		SizeIncrease = 1.75f;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Invalid Upgradelevel for Behemoth"));
		break;
	}}
