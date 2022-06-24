// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/Inu/States/InuBaseState.h"
#include "InuRetreatState.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UInuRetreatState : public UInuBaseState
{
	GENERATED_BODY()

	virtual void OnStateEnter(UStateMachine* StateMachine) override;
	virtual void OnStateExit() override;
	virtual void OnStateUpdate(float DeltaTime) override;

	FVector RetreatLocation;
	float Duration = 2.f;	
};
