// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUpgrade.h"
#include "RangedOnlyUpgradeComponent.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API URangedOnlyUpgradeComponent : public UBaseUpgrade
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
