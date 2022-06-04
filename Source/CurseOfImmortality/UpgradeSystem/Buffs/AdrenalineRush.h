// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "AdrenalineRush.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API UAdrenalineRush final : public UBaseBuff
{
	GENERATED_BODY()

public:

	virtual bool AddBuffStack() override;
	virtual void OnBuffBegin() override;
	virtual void OnBuffEnd() override;

private:
	float IncreaseValue = 100.0f;
};
