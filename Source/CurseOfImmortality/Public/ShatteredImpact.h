// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RangedOnlyUpgradeComponent.h"
#include "ShatteredImpact.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UShatteredImpact : public URangedOnlyUpgradeComponent
{
	GENERATED_BODY()

public:
	virtual void OnEnemyHit() override;
private:
	UPROPERTY()
	int SplitsRemaining = 1;
	UPROPERTY()
	int AmountOfFragments = 5;
};
