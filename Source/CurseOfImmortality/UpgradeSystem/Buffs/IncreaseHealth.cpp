// Fill out your copyright notice in the Description page of Project Settings.


#include "IncreaseHealth.h"

#include "CurseOfImmortality/UpgradeSystem/GameDummy/Char.h"


// Sets default values for this component's properties
UIncreaseHealth::UIncreaseHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
	DisplayName = "IncreaseHealth";
	CurrentStacks = 1;
	Stackable = true;
	CustomBuffEnd = true;
	StatModifier = true;
	StatModifications.Add(Health, IncreaseValue);
}

void UIncreaseHealth::AddBuffStack()
{
	Super::AddBuffStack();
	CurrentStacks ++;
	StatModifications[Health] += IncreaseValue;
	
}

void UIncreaseHealth::InitializeBuff(int Level, AChar* _Owner)
{
	Super::InitializeBuff(Level, _Owner);
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

