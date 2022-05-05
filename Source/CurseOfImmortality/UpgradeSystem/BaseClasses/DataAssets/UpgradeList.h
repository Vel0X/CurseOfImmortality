// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySpecification.h"
#include "UpgradeSpecification.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "UObject/Object.h"
#include "UpgradeList.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UUpgradeList final : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EUpgradeName>,UAbilitySpecification*> PossibleBaseAbilities;
	
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EUpgradeName>,UUpgradeSpecification*> PossibleUpgradeAbilities;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UBaseBuff>> Buffs;
};