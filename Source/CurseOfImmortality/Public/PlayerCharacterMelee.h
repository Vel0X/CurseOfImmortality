// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterBaseState.h"
#include "PlayerCharacterMelee.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UPlayerCharacterMelee : public UPlayerCharacterBaseState
{
	GENERATED_BODY()
		
public:
	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;
};
