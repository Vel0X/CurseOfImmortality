// Fill out your copyright notice in the Description page of Project Settings.


#include "SealOfCongruence.h"

void ASealOfCongruence::OnAbilityStart(int AbilityHandle)
{
	Super::OnAbilityStart(AbilityHandle);
	UE_LOG(LogTemp, Warning, TEXT("On Abilitystart was called in Seal of Congruence Upgrade"));
}

void ASealOfCongruence::OnAbilityEnd(int AbilityHandle)
{
	Super::OnAbilityEnd(AbilityHandle);
	UE_LOG(LogTemp, Warning, TEXT("On Abilityend was called in Seal of Congruence Upgrade"));
 
}
