// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "UObject/Object.h"
#include "Bleed.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API UBleed : public UBaseBuff
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBleed();

protected:
	// Called when the game starts

public:
	// Called every frame
	virtual void InitializeBuff(int Level, AChar* _Owner) override;
	virtual void AddBuffStack() override;

	virtual void OnBuffTick(float DeltaTime) override;

public:
	float TickInterval = 0.5f;
	float DamageAmount = 10.0f;
	float TimeUntilNextTick = 0.0f;
};