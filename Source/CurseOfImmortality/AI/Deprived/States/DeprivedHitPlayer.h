// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeprivedBaseState.h"
#include "DeprivedHitPlayer.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UDeprivedHitPlayer : public UDeprivedBaseState
{
	GENERATED_BODY()

public:
	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;
};
