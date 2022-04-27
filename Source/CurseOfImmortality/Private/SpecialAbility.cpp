// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialAbility.h"


void ASpecialAbility::InitializeAbility_Implementation(int _AbilityHandle, AActor* Caster, int Level)
{
	Super::InitializeAbility_Implementation(_AbilityHandle, Caster, Level);
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
