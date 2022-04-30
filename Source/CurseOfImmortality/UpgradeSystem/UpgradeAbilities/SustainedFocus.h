// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseUpgrade.h"
#include "SustainedFocus.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API USustainedFocus : public UBaseUpgrade
{
	GENERATED_BODY()

	virtual void InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel) override;
	virtual void OnAbilityStart(int AbilityHandle) override;

private:
	float DurationModifier = 1.25f;
	
};
