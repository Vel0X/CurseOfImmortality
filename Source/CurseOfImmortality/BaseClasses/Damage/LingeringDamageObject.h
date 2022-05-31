// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageObject.h"
#include "UObject/Object.h"
#include "LingeringDamageObject.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ULingeringDamageObject : public UDamageObject
{
	GENERATED_BODY()

public:
	virtual bool DealDamage(ABaseCharacter* Character) override;

	virtual void Tick(float DeltaTime) override;
	
	float TimeUntilNextHit = 0.0f;
	float  HitTimer = 0.5f;
};
