// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/Inu/States/InuBaseState.h"
#include "InuFindStartLocation.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UInuFindStartLocation : public UInuBaseState
{
	GENERATED_BODY()

	virtual void OnStateEnter(UStateMachine* StateMachine) override;
	virtual void OnStateExit() override;
	virtual void OnStateUpdate(float DeltaTime) override;

	TArray<FVector> Path;
	FVector RandomLocation;
	int PathIndex = 0;
	float PathfindingTimer;

	bool MoveInLocationArrived = false;

	FVector MoveInLocation;

	float WalkInDuration = 0.5f;
};
