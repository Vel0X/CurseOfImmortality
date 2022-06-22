// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/DamageSpecification.h"
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

	TArray<FDamageFormula> Formulas;

	bool ScaleWithAbilityLevel;

	virtual void SetupDamageObject(const UDamageSpecification* Specification);

	virtual bool DealDamage(ABaseCharacter* Character);

	virtual void Tick(float DeltaTime);

	UPROPERTY(EditAnywhere)
	TArray<ABaseCharacter*> HitCharacters;
	UPROPERTY(EditAnywhere)
	ABaseCharacter* OwningChar;

	UPROPERTY(EditAnywhere)
	ABaseAbility* DamagingAbility;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* HitVfx;

	float TickInterval;
};
