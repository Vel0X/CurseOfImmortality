// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Assortment.h"
#include "UObject/Object.h"
#include "StormcallerCircleAssortment.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UStormcallerCircleAssortment : public UAssortment
{
	GENERATED_BODY()

public:
	virtual void SpawnAssortment() override;
};
