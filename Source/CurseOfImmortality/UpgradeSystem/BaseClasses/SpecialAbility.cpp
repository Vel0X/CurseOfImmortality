// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecialAbility.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"

void ASpecialAbility::InitializeAbility(ABaseCharacter* _Caster, int Level, const UAbilitySpecification* AbilitySpecification)
{
	Super::InitializeAbility(_Caster, Level, AbilitySpecification);
	Parent = _Caster->GetAttachmentLocation(AttachmentPoint);
}

void ASpecialAbility::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(Parent != nullptr)
		SetActorLocation(Parent->GetComponentLocation());
}
