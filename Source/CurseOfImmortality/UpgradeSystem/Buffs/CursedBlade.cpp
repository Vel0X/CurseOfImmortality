// Fill out your copyright notice in the Description page of Project Settings.


#include "CursedBlade.h"
#include "NiagaraComponent.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"

void UCursedBlade::InitializeBuff(int Level, ABaseCharacter* _Owner, ABaseCharacter* _Inflicter)
{
	Super::InitializeBuff(Level, _Owner, _Inflicter);
	ParticleSystemComponent = SetupVfx(UpperPoint);

	switch(Level)
	{
	case 1:
		DamageAmount = 100.0f;
		break;
	case 2:
		DamageAmount = 200.0f;
		break;
	case 3:
		DamageAmount = 300.0f;
		break;
	default: ;
	}
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
		Owner->TakeDmg(DamageAmount, Inflicter, nullptr, true);
	}
}
