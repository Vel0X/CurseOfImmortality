// Fill out your copyright notice in the Description page of Project Settings.


#include "IncreaseHealth.h"


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

