// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseUpgrade.h"
#include "SharpenedReflexes.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API USharpenedReflexes final : public UBaseUpgrade
{
	GENERATED_BODY()

public:
	virtual void InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel) override;

	virtual void OnAbilityHit(ARangedAbility* Ability) override;
};
