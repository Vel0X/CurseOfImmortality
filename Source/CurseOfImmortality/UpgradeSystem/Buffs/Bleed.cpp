// Fill out your copyright notice in the Description page of Project Settings.


#include "Bleed.h"

UBleed::UBleed()
{
	BuffDuration = 5.0f;
	RemainingDuration = BuffDuration;
	CurrentStacks = 1;
	Stackable = true;
	CustomBuffEnd = false;
	StatModifier = false;
}

void UBleed::OnBuffTick(float DeltaTime)
{
	Super::OnBuffTick(DeltaTime);
	if(TimeUntilNextTick <= 0.0f)
	{
		//Deal Damage
		TimeUntilNextTick = TickInterval;
	}
	else
	{
		TimeUntilNextTick -= DeltaTime;
	}
}
