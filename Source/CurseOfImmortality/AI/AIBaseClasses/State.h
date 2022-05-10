// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "State.generated.h"
/**
 * 
 */
class ABaseCharacter;
class ABaseEnemyPawn;
class UStateMachine;
UCLASS()
class CURSEOFIMMORTALITY_API UState : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnStateEnter(UStateMachine* StateMachine);

	virtual void OnStateExit();

	virtual void OnStateUpdate(float DeltaTime);

	bool Verbose = false;
};
