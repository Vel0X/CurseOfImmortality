// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "SpecialAbility.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ASpecialAbility : public ABaseAbility
{
	GENERATED_BODY()
public:
	virtual void InitializeAbility(int _AbilityHandle, AChar* _Caster, int Level) override;

	UPROPERTY(EditAnywhere)
	AActor* Parent;
protected:
	void Tick(float DeltaSeconds) override;
};
