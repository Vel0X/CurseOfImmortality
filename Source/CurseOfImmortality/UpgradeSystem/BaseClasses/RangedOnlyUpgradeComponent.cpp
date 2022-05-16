// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedOnlyUpgradeComponent.h"

void URangedOnlyUpgradeComponent::BeginPlay()
{
	Super::BeginPlay();
	RestrictedTo = Ranged;
}
