// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseUpgrade.h"
#include "Behemoth.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UBehemoth final : public UBaseUpgrade
{
	GENERATED_BODY()

public:

	virtual void OnAbilityStart() override;
	virtual void InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel) override;

private:
	UPROPERTY(EditAnywhere)
	float SizeIncrease = 1.25f;

	UPROPERTY(EditAnywhere)
	bool Proc = false; //Size multiplication should happen only once
};
