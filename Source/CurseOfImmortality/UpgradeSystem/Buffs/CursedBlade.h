// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "CursedBlade.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UCursedBlade : public UBaseBuff
{
	GENERATED_BODY()

	
public:
	// Sets default values for this component's properties
	UCursedBlade();

	virtual void InitializeBuff(int Level, ABaseCharacter* _Owner) override;
	virtual void OnBuffBegin() override;
	virtual void OnBuffEnd() override;
	virtual void OnTakeDamage(ABaseAbility* Ability) override;
};
