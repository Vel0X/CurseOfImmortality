// Fill out your copyright notice in the Description page of Project Settings.


#include "Bleed.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"

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
		Owner->TakeDmg(DamageAmount, Inflicter, nullptr, false);
		TimeUntilNextTick = TickInterval;
	}
	else
	{
		TimeUntilNextTick -= DeltaTime;
	}
}
