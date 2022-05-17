// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseUpgrade.h"
#include "CursemarkOfDoom.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UCursemarkOfDoom: public UBaseUpgrade
{
	GENERATED_BODY()

public:
	virtual void OnEnemyHit(ABaseCharacter* Enemy) override;
	virtual void InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel) override;

private:
	UPROPERTY(EditAnywhere)
	int PiercesLeft = 1;
};
