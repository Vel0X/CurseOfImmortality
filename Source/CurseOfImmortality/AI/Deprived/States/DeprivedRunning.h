// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeprivedBaseState.h"
#include "DeprivedRunning.generated.h"

class UDeprivedStateMachine;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UDeprivedRunning : public UDeprivedBaseState
{
	GENERATED_BODY()

public:
	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;

private:	
	TArray<FVector> Path;
	
	int PathIndex = 0;
	
	float PathfindingTimer = 0.f;

	bool NoAttackChosen = true;
};
