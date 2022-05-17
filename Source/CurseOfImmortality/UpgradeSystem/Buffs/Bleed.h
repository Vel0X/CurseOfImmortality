// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "Bleed.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API UBleed : public UBaseBuff
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBleed();

public:
	// Called every frame
	virtual void InitializeBuff(int Level, ABaseCharacter* _Owner) override;
	virtual void AddBuffStack() override;
	virtual void OnBuffEnd() override;
	virtual void OnBuffTick(float DeltaTime) override;
	float TickInterval = 0.5f;
	float DamageAmount = 10.0f;
	float TimeUntilNextTick = 0.0f;
};