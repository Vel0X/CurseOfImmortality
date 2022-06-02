// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageObject.h"

#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/DamageSpecification.h"

void UDamageObject::SetupDamageObject(const UDamageSpecification* Specification)
{
	Damage = Specification->Damage;
}

bool UDamageObject::DealDamage(ABaseCharacter* Character)
{
	if(!HitCharacters.Contains(Character))
	{
		//UE_LOG(LogTemp, Warning, TEXT("DMG"));
		Character->TakeDmg(Damage, OwningChar, DamagingAbility, true);
		HitCharacters.Add(Character);
		return true;
	}
	return false;
}

void UDamageObject::Tick(float DeltaTime)
{
}
