// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/Inu/States/InuBaseState.h"
#include "InuRunningState.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UInuRunningState : public UInuBaseState
{
	GENERATED_BODY()

	virtual void OnStateEnter(UStateMachine* StateMachine) override;
	virtual void OnStateExit() override;
	virtual void OnStateUpdate(float DeltaTime) override;

	TArray<FVector> Path;
	
	float PathfindingTimer = 0.f;
	int PathIndex = 0;
};
