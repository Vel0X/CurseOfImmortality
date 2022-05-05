// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "UObject/Object.h"
#include "BaseStatSpecification.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UBaseStatSpecification final : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> BaseStats = {
		{Health, 10.0f},
		{PhysicalDamage, 10.0f},
		{Soul, 10.0f},
		{Arcane, 10.0f},
		{Astrality, 10.0f},
		{Ruin, 10.0f},
		{Gravity, 10.0f},
		{Faith, 10.0f},
		{Movespeed, 10.0f}
	};
};
