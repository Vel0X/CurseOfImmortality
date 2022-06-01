// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "IncreaseHealth.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API UIncreaseHealth : public UBaseBuff
{
	GENERATED_BODY()

public:

	virtual void AddBuffStack() override;
	virtual void OnBuffBegin() override;

	virtual void OnBuffEnd() override;

private:
	float IncreaseValue = 100.0f;
};
