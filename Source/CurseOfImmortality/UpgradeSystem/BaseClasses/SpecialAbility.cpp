// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialAbility.h"


void ASpecialAbility::InitializeAbility(int _AbilityHandle, AChar* _Caster, int Level)
{
	Super::InitializeAbility(_AbilityHandle, Caster, Level);
}

void ASpecialAbility::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(Caster != nullptr)
	{
		SetActorLocation(Caster->GetActorLocation());
	}
}
