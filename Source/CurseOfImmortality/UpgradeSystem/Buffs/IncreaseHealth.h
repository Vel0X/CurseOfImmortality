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
	// Sets default values for this component's properties
	UIncreaseHealth();

protected:

public:

	virtual void IntitializeBuff(int Level, AChar* _Owner) override;
	virtual void OnBuffBegin() override;

	virtual void OnBuffEnd() override;
};
