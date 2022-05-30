// Fill out your copyright notice in the Description page of Project Settings.


#include "CursedBlade.h"
#include "NiagaraComponent.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"

UCursedBlade::UCursedBlade()
{
	DisplayName = "Cursed Blade";
	BuffDuration = 5.0f;
	RemainingDuration = BuffDuration;
	CurrentStacks = 1;
	Stackable = false;
	RefreshOnNew = false;
	CustomBuffEnd = false;
	StatModifier = false;
	BuffType = CursedBlade;
}

void UCursedBlade::InitializeBuff(int Level, ABaseCharacter* _Owner)
{
	Super::InitializeBuff(Level, _Owner);
	ParticleSystem = SetupVfx(UpperPoint);
}

void UCursedBlade::OnBuffBegin()
{
	Super::OnBuffBegin();
}

void UCursedBlade::OnBuffEnd()
{
	Super::OnBuffEnd();
	DestroyVfx();
}

void UCursedBlade::OnTakeDamage(ABaseAbility* Ability)
{
	Super::OnTakeDamage(Ability);
	if(Ability != nullptr && Ability->AbilityType == Melee)
	{
		if(ParticleSystem != nullptr)
		{
			ParticleSystem->SetBoolParameter("User.Dissolve", true);
			ParticleSystem->Deactivate();
		}
		Owner->RemoveBuff(this);
		Owner->TakeDmg(20, nullptr, nullptr);
	}
}
