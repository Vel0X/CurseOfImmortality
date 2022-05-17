// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecialAbility.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"

void ASpecialAbility::InitializeAbility(int _AbilityHandle, ABaseCharacter* _Caster, int Level)
{
	Super::InitializeAbility(_AbilityHandle, Caster, Level);
	Parent = Caster;
}

void ASpecialAbility::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(Parent != nullptr)
	{
		SetActorLocation(Parent->GetActorLocation());
	}
}
