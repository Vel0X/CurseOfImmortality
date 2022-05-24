// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "UObject/Object.h"
#include "Assortment.generated.h"

class ABaseEnemyPawn;
class UAssortmentSpecification;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UAssortment : public UObject
{
	GENERATED_BODY()

public:
	virtual TArray<ABaseEnemyPawn*> SpawnAssortment();


	/**
	 * Transfer the Values from the Specification into the member variables of the Assortment
	 *
	 */
	void Initialize(const UAssortmentSpecification* AssortmentSpecification);


	/**
	 * Determine how many enemies will be spawned, so that the powerlevel of this assortment can be accurately calculated
	 *
	 */
	void Determine();


	int CalculatePowerLevel();

	TMap<TEnumAsByte<EEnemy>, int> EnemiesMap;

};
