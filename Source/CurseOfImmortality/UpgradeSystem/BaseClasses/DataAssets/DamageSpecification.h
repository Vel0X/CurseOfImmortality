// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageFormula.h"
#include "DamageSpecification.generated.h"


class UDamageObject;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UDamageSpecification : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, Category="Level")
	bool ScaleWithAbilityLevel;
	
	/** How to calculate the Damage. Can be specified on a per Level Basis. If this Damageobject does not have levels the first entry will be picked */
	UPROPERTY(EditAnywhere)
	TArray<FDamageFormula> DamageFormulas; 
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageObject> Class;

	/** In which time interval damage will be dealt */
	UPROPERTY(EditAnywhere, Category="LingeringDamageObjectSettings")
	float HitTimer = 0.5f;
};
