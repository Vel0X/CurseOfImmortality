// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "CurseOfImmortality/Management/Rounds/Assortments/Assortment.h"
#include "UObject/Object.h"
#include "AssortmentSpecification.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UAssortmentSpecification : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString DisplayName;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAssortment> Class;
	
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EEnemy>, int> Enemies;

	UPROPERTY(EditAnywhere)
	int PowerLevel = 0;
};
