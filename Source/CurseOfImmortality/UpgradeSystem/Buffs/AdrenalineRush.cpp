// Fill out your copyright notice in the Description page of Project Settings.


#include "AdrenalineRush.h"

void UAdrenalineRush::AddBuffStack()
{
	Super::AddBuffStack();
	CurrentStacks ++;
	StatModifications[AttackSpeed] += IncreaseValue;
	
}

void UAdrenalineRush::OnBuffBegin()
{
	Super::OnBuffBegin();
}

void UAdrenalineRush::OnBuffEnd()
{
	Super::OnBuffEnd();
	
}

