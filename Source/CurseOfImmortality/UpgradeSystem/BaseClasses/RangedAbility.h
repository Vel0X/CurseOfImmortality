// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "RangedAbility.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ARangedAbility : public ABaseAbility
{
	GENERATED_BODY()


public:
	bool CanInteract = true;

	virtual void OnInteraction(ABaseAbility* OtherAbility);
	
protected:
	virtual void BeginPlay() override;
};
