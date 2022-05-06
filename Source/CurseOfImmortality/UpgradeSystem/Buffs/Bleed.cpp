// Fill out your copyright notice in the Description page of Project Settings.


#include "Bleed.h"

#include "CurseOfImmortality/UpgradeSystem/GameDummy/Char.h"

UBleed::UBleed()
{
	DisplayName = "Bleed";
	BuffDuration = 5.0f;
	RemainingDuration = BuffDuration;
	TimeUntilNextTick = TickInterval;
	CurrentStacks = 1;
	Stackable = true;
	RefreshOnNew = true;
	CustomBuffEnd = false;
	StatModifier = false;
	BuffType = Bleed;
}

void UBleed::InitializeBuff(int Level, AChar* _Owner)
{
	Super::InitializeBuff(Level, _Owner); 
}

void UBleed::AddBuffStack()
{
	Super::AddBuffStack();
	RemainingDuration = BuffDuration;
	DamageAmount += DamageAmount / static_cast<float>(CurrentStacks);
	CurrentStacks++;
}

void UBleed::OnBuffTick(float DeltaTime)
{
	Super::OnBuffTick(DeltaTime);
	if(TimeUntilNextTick <= 0.0f)
	{
		//Deal Damage
		Owner->TakeDmg(DamageAmount, true);
		TimeUntilNextTick = TickInterval;
	}
	else
	{
		TimeUntilNextTick -= DeltaTime;
	}
}
