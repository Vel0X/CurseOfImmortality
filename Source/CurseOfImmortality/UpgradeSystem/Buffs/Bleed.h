// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "Bleed.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API UBleed final : public UBaseBuff
{
	GENERATED_BODY()

public:
	virtual void InitializeBuff(int Level, ABaseCharacter* _Owner, ABaseCharacter* _Inflicter) override;
	virtual void AddBuffStack() override;
	virtual void OnBuffEnd() override;
	virtual void OnBuffTick(float DeltaTime) override;
	float TickInterval = 0.2f;
	float DamageAmount = 5.0f;
	float TimeUntilNextTick = 0.0f;
};