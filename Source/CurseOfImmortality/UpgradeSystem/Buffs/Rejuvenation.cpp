// Fill out your copyright notice in the Description page of Project Settings.


#include "Rejuvenation.h"

#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"

URejuvenation::URejuvenation()
{
	/*
	DisplayName = "Rejuvenation";
	CurrentStacks = 1;
	Stackable = true;
	CustomBuffEnd = true;
	StatModifier = false;
	*/
}

void URejuvenation::AddBuffStack()
{
	Super::AddBuffStack();
	CurrentStacks++;
	HealAmount += HealAmount / static_cast<float>(CurrentStacks);
	UE_LOG(LogTemp, Warning, TEXT("Stack was added" ));
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
