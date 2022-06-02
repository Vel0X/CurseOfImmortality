// Fill out your copyright notice in the Description page of Project Settings.


#include "CursedBlade.h"
#include "NiagaraComponent.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"

void UCursedBlade::InitializeBuff(int Level, ABaseCharacter* _Owner, ABaseCharacter* _Inflicter)
{
	Super::InitializeBuff(Level, _Owner, _Inflicter);
	ParticleSystemComponent = SetupVfx(UpperPoint);
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
		if(ParticleSystemComponent != nullptr)
		{
			ParticleSystemComponent->SetBoolParameter("User.Dissolve", true);
			ParticleSystemComponent->Deactivate();
		}
		Owner->RemoveBuff(this);
		Owner->TakeDmg(20, Inflicter, nullptr);
	}
}
