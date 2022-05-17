// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	FString DisplayName;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EUpgradeName> AbilityName;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAbilityType> AbilityType;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseAbility> Class;

	UPROPERTY(EditAnywhere)
	int MaxLevel = 3;

	//needs to be the same length as max Levels
	UPROPERTY(EditAnywhere)
	TArray<float> Cooldown;

	UPROPERTY(EditAnywhere)
	int InitialWeight = 100;
};
