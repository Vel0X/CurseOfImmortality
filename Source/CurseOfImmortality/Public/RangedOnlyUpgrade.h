// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUpgrade.h"
#include "RangedOnlyUpgrade.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ARangedOnlyUpgrade : public ABaseUpgrade
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
