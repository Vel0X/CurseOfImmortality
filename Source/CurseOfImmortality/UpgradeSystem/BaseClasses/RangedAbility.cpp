// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedAbility.h"

void ARangedAbility::BeginPlay()
{
	Super::BeginPlay();
	DestroyOnEnemyHit = true;
}