// Fill out your copyright notice in the Description page of Project Settings.

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
	USoulFlayer();

	virtual void InitializeBuff(int Level, ABaseCharacter* _Owner, ABaseCharacter* _Inflicter) override;
	virtual void OnBuffEnd() override;
	virtual void OnBuffTick(float DeltaTime) override;
	virtual void OnDealDamage(float Amount, ABaseCharacter* Recipient) override;

public:
	float TickInterval = 0.5f;
	float DamageAmount = 10.0f;
	float TimeUntilNextTick = 0.0f;

	float DamageIncrease = 5.0f;
	float MoveSpeedIncrease = 500.0f;

	float HealPercentage = 0.5f;
};
