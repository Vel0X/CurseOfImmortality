// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySpecification.h"
#include "NiagaraSystem.h"
#include "UpgradeSpecification.h"
#include "CurseOfImmortality/Enemies/EnemySpecification.h"
#include "CurseOfImmortality/Management/Rounds/DataAssets/AssortmentSpecification.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "SpawnablesList.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API USpawnablesList final : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EUpgradeName>,UAbilitySpecification*> PossibleBaseAbilities;
	
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EUpgradeName>,UUpgradeSpecification*> PossibleUpgradeAbilities;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EBuff>, UBuffSpecification*> Buffs;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EBuff>, UNiagaraSystem*> BuffVFX;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EEnemy>, UEnemySpecification*> Enemies;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EAssortment>, UAssortmentSpecification*> Assortments;
};