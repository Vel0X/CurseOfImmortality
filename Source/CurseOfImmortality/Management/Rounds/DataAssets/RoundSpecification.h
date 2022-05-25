// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "RoundSpecification.generated.h"

/**
 * the Details of each round
 */
UCLASS()
class CURSEOFIMMORTALITY_API URoundSpecification : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * How likely each enemy is to occur in a round
	 */
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EEnemy>, float> EnemyWeights;


	/**
	 * How likely each assortment is to occur in a round
	 */
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EAssortment>, float> AssortmentWeights;

	/**
	 * the percentage of the powerlevel, that gets filled up with assortments. The Rest will then be filled up by single enemies
	 */
	UPROPERTY(EditAnywhere)
	float AssortmentRatio; 


	/**
	 * How strong the round will be (The sum of all enemies and assortments present in it)
	 */
	UPROPERTY(EditAnywhere)
	int TargetPowerlevel;

	/**
	 * How many stages the round has
	 */
	UPROPERTY(EditAnywhere)
	int Stages;
	
	/**
	 * the time, when to initiate the next stage of the round, based on the current remaining powerlevel.
	 * Length needs to be the same as Stages
	 */
	UPROPERTY(EditAnywhere)
	TArray<int> PowerLevelTransitionThreshhold; 

	
	/**
	 * the time, when to initiate the next stage of the round, based on the remaining time
	* Length needs to be the same as Stages
	*/
	UPROPERTY(EditAnywhere)
	TArray<float> TimeTransitionThreshhold; 
};
