// Fill out your copyright notice in the Description page of Project Settings.


#include "IncreaseHealth.h"


bool UIncreaseHealth::AddBuffStack()
{
	return Super::AddBuffStack();
	
}

void UIncreaseHealth::OnBuffBegin()
{
	Super::OnBuffBegin();
}

void UIncreaseHealth::OnBuffEnd()
{
	Super::OnBuffEnd();
	
}

