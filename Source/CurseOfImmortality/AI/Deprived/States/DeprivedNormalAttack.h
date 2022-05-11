// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeprivedBaseState.h"
#include "DeprivedNormalAttack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CURSEOFIMMORTALITY_API UDeprivedNormalAttack : public UDeprivedBaseState
{
	GENERATED_BODY()

public:
	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	bool LeftHandCanAttack = true;
	UPROPERTY(BlueprintReadWrite)
	bool RightHandCanAttack = true;
};
