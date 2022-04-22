// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RangedOnlyUpgradeComponent.h"
#include "Pierce.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UPierce final: public URangedOnlyUpgradeComponent
{
	GENERATED_BODY()

public:
	virtual void OnEnemyHit() override;

private:
	UPROPERTY(EditAnywhere)
	int PiercesLeft = 1;
};
