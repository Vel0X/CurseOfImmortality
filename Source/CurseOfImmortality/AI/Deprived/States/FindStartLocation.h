// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeprivedBaseState.h"
#include "FindStartLocation.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UFindStartLocation : public UDeprivedBaseState
{
	GENERATED_BODY()

public:
	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;

private:
	TArray<FVector> Path;
	FVector RandomLocation = FVector::Zero();
	FVector MoveInLocation = FVector::Zero();

	float PathfindingTimer = 0.f;
	float WalkInDuration = 1.f;
	int PathIndex = 0;
	bool MoveInLocationArrived = false;
};
