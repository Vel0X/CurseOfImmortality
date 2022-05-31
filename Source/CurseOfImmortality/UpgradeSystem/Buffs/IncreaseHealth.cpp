// Fill out your copyright notice in the Description page of Project Settings.


#include "IncreaseHealth.h"


UIncreaseHealth::UIncreaseHealth()
{
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

void UIncreaseHealth::OnBuffBegin()
{
	Super::OnBuffBegin();
}

void UIncreaseHealth::OnBuffEnd()
{
	Super::OnBuffEnd();
	
}

