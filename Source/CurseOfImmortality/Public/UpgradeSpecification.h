// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUpgrade.h"
#include "Engine/DataAsset.h"
#include "UpgradeSpecification.generated.h"

UENUM()
enum EUpgradeName
{
	Fireball,
	SealOfCongruence, 
	Pierce,            
	ShatteredImpact    
};

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UUpgradeSpecification final : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EUpgradeName> UpgradeName;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseUpgrade> Class;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAbilityType> Application;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EUpgradeName>> Restrictions;

	UPROPERTY(EditAnywhere)
	int MaxLevel = 3;

	UPROPERTY(EditAnywhere)
	int InitialWeight = 100;
};
