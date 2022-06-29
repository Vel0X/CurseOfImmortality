﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "Rejuvenation.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom))
class CURSEOFIMMORTALITY_API URejuvenation : public UBaseBuff
{
	GENERATED_BODY()
public:
	virtual bool AddBuffStack() override;

	virtual void InitializeBuff(int Level, ABaseCharacter* _Owner, ABaseCharacter* _Inflicter) override;
	virtual void OnBuffTick(float DeltaTime) override;
	virtual void OnBuffEnd() override;

private:
	float TimeUntilNextTick = 0.0f;
	float TickInterval = 0.3f;
	float HealAmount = 6.0f;
};

