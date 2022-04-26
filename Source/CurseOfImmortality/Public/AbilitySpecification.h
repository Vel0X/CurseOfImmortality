// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "UpgradeSpecification.h"
#include "Engine/DataAsset.h"
#include "AbilitySpecification.generated.h"


/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UAbilitySpecification final: public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EUpgradeName> AbilityName;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAbilityType> AbilityType;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseAbility> Class;

	UPROPERTY(EditAnywhere)
	int MaxLevel = 3;

	UPROPERTY(EditAnywhere)
	int InitialWeight = 100;
};