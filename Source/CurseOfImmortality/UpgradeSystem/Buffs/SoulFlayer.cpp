// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulFlayer.h"

#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"

void USoulFlayer::InitializeBuff(int Level, ABaseCharacter* _Owner, ABaseCharacter* _Inflicter)
{
	Super::InitializeBuff(Level, _Owner, _Inflicter);
	ParticleSystemComponent = SetupVfx(LowerPoint);
}

void USoulFlayer::OnBuffEnd()
{
	Super::OnBuffEnd();
	DestroyVfx();
}

void USoulFlayer::OnBuffTick(float DeltaTime)
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

void USoulFlayer::OnDealDamage(const float Amount, ABaseCharacter* Recipient)
{
	Super::OnDealDamage(Amount, Recipient);

	//lifesteal
	const float HealAmount = Amount * HealPercentage;
	Owner->Heal(HealAmount);
}
