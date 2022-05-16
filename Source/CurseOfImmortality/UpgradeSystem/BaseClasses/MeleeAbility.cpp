// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAbility.h"

void AMeleeAbility::InitializeAbility(int _AbilityHandle, ABaseCharacter* _Caster, int Level)
{
	Super::InitializeAbility(_AbilityHandle, _Caster, Level);
}

void AMeleeAbility::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
