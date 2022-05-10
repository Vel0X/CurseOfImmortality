// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulFlayer.h"

#include "CurseOfImmortality/UpgradeSystem/GameDummy/Char.h"

USoulFlayer::USoulFlayer()
{
	DisplayName = "Soul Flayer";
	BuffDuration = 5.0f;
	RemainingDuration = BuffDuration;
	TimeUntilNextTick = TickInterval;
	CurrentStacks = 1;
	Stackable = false;
	RefreshOnNew = false;
	CustomBuffEnd = false;
	StatModifier = true;
	BuffType = SoulFlayer;
	StatModifications.Add(EStats::PhysicalDamage, DamageIncrease);
	StatModifications.Add(EStats::Movespeed, MoveSpeedIncrease);

}

void USoulFlayer::InitializeBuff(int Level, AChar* _Owner)
{
	Super::InitializeBuff(Level, _Owner);
}

void USoulFlayer::OnBuffEnd()
{
	Super::OnBuffEnd();
}

void USoulFlayer::OnBuffTick(float DeltaTime)
{
	Super::OnBuffTick(DeltaTime);
	if(TimeUntilNextTick <= 0.0f)
	{
		//Deal Damage
		Owner->TakeDmg(DamageAmount, nullptr, nullptr, true);
		TimeUntilNextTick = TickInterval;
	}
	else
	{
		TimeUntilNextTick -= DeltaTime;
	}
}
