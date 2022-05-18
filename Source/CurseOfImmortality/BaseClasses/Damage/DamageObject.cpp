﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageObject.h"

#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/DamageSpecification.h"

void UDamageObject::SetupDamageObject(const UDamageSpecification* Specification)
{
	Damage = Specification->Damage;
}

void UDamageObject::DealDamage(ABaseCharacter* Character)
{
	if(!HitCharacters.Contains(Character))
	{
		Character->TakeDmg(Damage, nullptr, nullptr, true);
		HitCharacters.Add(Character);
	}
}

void UDamageObject::Tick(float DeltaTime)
{
}