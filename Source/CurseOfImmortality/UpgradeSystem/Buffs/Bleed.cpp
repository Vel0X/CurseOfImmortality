// Fill out your copyright notice in the Description page of Project Settings.


#include "Bleed.h"

#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"

UBleed::UBleed()
{
	/*
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
	*/
}

void UBleed::InitializeBuff(int Level, ABaseCharacter* _Owner, ABaseCharacter* _Inflicter)
{
	Super::InitializeBuff(Level, _Owner, _Inflicter);
	ParticleSystemComponent = SetupVfx(CenterPoint);
}

void UBleed::AddBuffStack()
{
	Super::AddBuffStack();
	RemainingDuration = BuffDuration;
	DamageAmount += DamageAmount / static_cast<float>(CurrentStacks);
	CurrentStacks++;
}

void UBleed::OnBuffEnd()
{
	Super::OnBuffEnd();
	DestroyVfx();
}

void UBleed::OnBuffTick(float DeltaTime)
{
	Super::OnBuffTick(DeltaTime);
	if(TimeUntilNextTick <= 0.0f)
	{
		//Deal Damage
		Owner->TakeDmg(DamageAmount, Inflicter, nullptr, true);
		TimeUntilNextTick = TickInterval;
	}
	else
	{
		TimeUntilNextTick -= DeltaTime;
	}
}
