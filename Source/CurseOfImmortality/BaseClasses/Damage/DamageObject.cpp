// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageObject.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/DamageSpecification.h"

void UDamageObject::SetupDamageObject(const UDamageSpecification* Specification)
{
	ScaleWithAbilityLevel = Specification->ScaleWithAbilityLevel;
	Formulas = Specification->DamageFormulas;
	Damage = Specification->Damage;
	TickInterval = Specification->HitTimer;
}

bool UDamageObject::DealDamage(ABaseCharacter* Character)
{
	if(HitCharacters.Contains(Character))
	{
		return false;

	}

	//check if Handle is contained in DamageReceiverHandle
	if(DamagingAbility &&
		DamagingAbility->AbilityHandle != -1 &&
		Character->DamageReceiverHandleContained(DamagingAbility->AbilityHandle))
	{
		return false;
	}
	
	if(ScaleWithAbilityLevel && DamagingAbility)
	{
		if(Formulas.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("No Formulas were specified for DamageObject"));
			return false;
		}

		const int AbilityLevel = DamagingAbility->AbilityLevel;
		if(Formulas.Num()<AbilityLevel)
		{
			UE_LOG(LogTemp, Error, TEXT("Ability was at Level %i, but only %i Formulas were specified"), AbilityLevel, Formulas.Num());
			return false;
		}

		const auto [BaseDamage, ScaleFactor, Variation] = Formulas[AbilityLevel-1];
		if(!OwningChar)
		{
			UE_LOG(LogTemp, Error, TEXT("Owning Char can not be null"));
			return false;
		}

		const float Amount = (BaseDamage + ScaleFactor * OwningChar->Stats[PhysicalDamage]) * (1 + FMath::FRandRange(-Variation, Variation));
		Character->TakeDmg(Amount, OwningChar, DamagingAbility, true);

		if(DamagingAbility->AbilityHandle != -1)
		{
			const float Expiration = TickInterval - 0.02f;
			Character->DamageReceiverHandles.Add(FDamageReceiverHandle(DamagingAbility->AbilityHandle, Expiration));
		}
	}
	else
	{
		Character->TakeDmg(Damage, OwningChar, DamagingAbility, true);
	}
	
	HitCharacters.Add(Character);
	return true;
}

void UDamageObject::Tick(float DeltaTime)
{
}
