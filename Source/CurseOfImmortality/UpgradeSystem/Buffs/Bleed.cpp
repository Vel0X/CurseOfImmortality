// Fill out your copyright notice in the Description page of Project Settings.


#include "Bleed.h"

#include "NiagaraComponent.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"

void UBleed::InitializeBuff(int Level, ABaseCharacter* _Owner, ABaseCharacter* _Inflicter)
{
	Super::InitializeBuff(Level, _Owner, _Inflicter);
	ParticleSystemComponent = SetupVfx(CenterPoint);
	ParticleSystemComponent->SetIntParameter("User.CurrentStacks", 1);
}

bool UBleed::AddBuffStack()
{
	const bool AddedStack = Super::AddBuffStack();

	if(AddedStack)
	{
		DamageAmount += DamageAmount / static_cast<float>(CurrentStacks-1);
		ParticleSystemComponent->SetIntParameter("User.CurrentStacks", CurrentStacks);
	}

	return AddedStack;
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
