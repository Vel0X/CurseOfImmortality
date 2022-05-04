﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Char.h"


// Sets default values
AChar::AChar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChar::RecalculateStats()
{
	for (auto Stat : Stats)
	{
		Stats[Stat.Key] = BaseStats->BaseStats[Stat.Key];
	}
	
	for (const auto Buff : Buffs)
	{
		if(!Buff->StatModifier)
			continue;

		for (const auto StatMod : Buff->StatModifications)
		{
			Stats[StatMod.Key] += StatMod.Value;
		}
	}
}

