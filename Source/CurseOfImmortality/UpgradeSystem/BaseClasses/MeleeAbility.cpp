// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAbility.h"

void AMeleeAbility::InitializeAbility(ABaseCharacter* _Caster, int Level, const UAbilitySpecification* AbilitySpecification)
{
	Super::InitializeAbility(_Caster, Level, AbilitySpecification);
}

void AMeleeAbility::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
