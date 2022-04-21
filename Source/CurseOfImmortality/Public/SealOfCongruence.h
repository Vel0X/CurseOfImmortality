// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUpgrade.h"
#include "RangedOnlyUpgrade.h"
#include "SealOfCongruence.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ASealOfCongruence : public ARangedOnlyUpgrade
{
	GENERATED_BODY()


protected:
	virtual void OnAbilityStart(int AbilityHandle) override;
	virtual void OnAbilityEnd(int AbilityHandle) override;
	
};
