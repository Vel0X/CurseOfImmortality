// Fill out your copyright notice in the Description page of Project Settings.


#include "Rejuvenation.h"

#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"

bool URejuvenation::AddBuffStack()
{
	const bool AddedStack = Super::AddBuffStack();
	if(AddedStack)
		HealAmount += HealAmount / static_cast<float>(CurrentStacks-1);

	return AddedStack;
}

void URejuvenation::OnBuffTick(float DeltaTime)
{
	Super::OnBuffTick(DeltaTime);

	if(TimeUntilNextTick <= 0.0f)
	{
		Owner->Heal(HealAmount, true);
		//Deal Damage
		TimeUntilNextTick = TickInterval;
	}
	else
	{
		TimeUntilNextTick -= DeltaTime;
	}
	
}
