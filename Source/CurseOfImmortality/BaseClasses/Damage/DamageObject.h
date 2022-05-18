// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DamageObject.generated.h"

class ABaseCharacter;
class UDamageSpecification;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UDamageObject : public UObject
{
	GENERATED_BODY()

public:
	float Damage;

	void SetupDamageObject(const UDamageSpecification* Specification);

	virtual void DealDamage(ABaseCharacter* Character);

	virtual void Tick(float DeltaTime);

	UPROPERTY(EditAnywhere)
	TArray<ABaseCharacter*> HitCharacters;
};
