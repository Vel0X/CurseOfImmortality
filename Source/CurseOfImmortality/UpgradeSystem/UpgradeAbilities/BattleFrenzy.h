// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseUpgrade.h"
#include "BattleFrenzy.generated.h"


UCLASS()
class CURSEOFIMMORTALITY_API UBattleFrenzy final : public UBaseUpgrade
{
	GENERATED_BODY()
public:
	virtual void OnEnemyHit(ABaseCharacter* Enemy) override;
	virtual void InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel) override;
};
