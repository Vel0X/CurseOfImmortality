// Fill out your copyright notice in the Description page of Project Settings.


#include "SharpenedReflexes.h"

void USharpenedReflexes::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
}

void USharpenedReflexes::OnAbilityHit(ARangedAbility* Ability)
{
	Super::OnAbilityHit(Ability);
	UE_LOG(LogTemp, Warning, TEXT("OnAbilityHit was triggered"));
	Ability->OnInteraction(AbilityInstance);
}
