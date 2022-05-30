// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "MeleeAbility.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AMeleeAbility : public ABaseAbility
{
	GENERATED_BODY()

public:
	virtual void InitializeAbility(ABaseCharacter* _Caster, int Level) override;

protected:
	virtual void Tick(float DeltaSeconds) override;
};
