﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "SoulFlayer.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API USoulFlayer final : public UBaseBuff
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USoulFlayer();

	// Called every frame
	virtual void InitializeBuff(int Level, ABaseCharacter* _Owner) override;
	virtual void OnBuffEnd() override;
	virtual void OnBuffTick(float DeltaTime) override;

public:
	float TickInterval = 0.5f;
	float DamageAmount = 10.0f;
	float TimeUntilNextTick = 0.0f;

	float DamageIncrease = 5.0f;
	float MoveSpeedIncrease = 5.0f;

	float HealAmount = 3.0f;
};