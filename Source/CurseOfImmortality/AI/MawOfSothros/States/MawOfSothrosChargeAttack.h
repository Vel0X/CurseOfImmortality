// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosBaseState.h"
#include "MawOfSothrosChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UMawOfSothrosChargeAttack : public UMawOfSothrosBaseState
{
	GENERATED_BODY()

	UMawOfSothrosChargeAttack();
	
	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;
};
