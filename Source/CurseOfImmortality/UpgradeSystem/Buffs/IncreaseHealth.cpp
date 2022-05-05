// Fill out your copyright notice in the Description page of Project Settings.


#include "IncreaseHealth.h"

#include "CurseOfImmortality/UpgradeSystem/GameDummy/Char.h"


// Sets default values for this component's properties
UIncreaseHealth::UIncreaseHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
	CurrentStacks = 1;
	Stackable = false;
	CustomBuffEnd = true;
	StatModifier = true;
	StatModifications.Add(Health, 100);
}

void UIncreaseHealth::IntitializeBuff(int Level, AChar* _Owner)
{
	Super::IntitializeBuff(Level, _Owner);
}


// Called every frame

void UIncreaseHealth::OnBuffBegin()
{
	Super::OnBuffBegin();
}

void UIncreaseHealth::OnBuffEnd()
{
	Super::OnBuffEnd();
	
}

