// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/StormCaller/States/StormCallerBaseState.h"
#include "StormCallerAttack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CURSEOFIMMORTALITY_API UStormCallerAttack : public UStormCallerBaseState
{
	GENERATED_BODY()

	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite)
	bool WaitForAnimation = false;
};
