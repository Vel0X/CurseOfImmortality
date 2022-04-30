// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseUpgrade.h"
#include "ArcaneReplicator.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UArcaneReplicator : public UBaseUpgrade
{
	GENERATED_BODY()

public:
	virtual void InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel) override;
protected:
	virtual void OnAbilityStart(int AbilityHandle) override;

//private:
	//UPROPERTY(EditAnywhere)
	//int ChargesLeft = 1;
	
};
