// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseUpgrade.h"
#include "ShatteredImpact.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UShatteredImpact : public UBaseUpgrade
{
	GENERATED_BODY()

public:
	virtual void OnEnemyHit() override;
	virtual void InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel) override;

private:
	UPROPERTY()
	int SplitsRemaining = 1;
	UPROPERTY()
	int AmountOfFragments = 5;
};
