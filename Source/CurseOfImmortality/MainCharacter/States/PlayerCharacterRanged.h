// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterBaseState.h"
#include "PlayerCharacterRanged.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UPlayerCharacterRanged : public UPlayerCharacterBaseState
{
	GENERATED_BODY()
	
public:
	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;

	float AnimationTime;
};
