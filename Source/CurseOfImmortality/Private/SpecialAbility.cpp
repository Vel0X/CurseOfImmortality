// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialAbility.h"

void ASpecialAbility::InitializeAbility(const int _AbilityHandle, AActor* Caster)
{
	Super::InitializeAbility(_AbilityHandle, Caster);
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
