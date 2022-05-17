// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageObject.h"
#include "DamageSpecification.generated.h"

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

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageObject> Class;
};
