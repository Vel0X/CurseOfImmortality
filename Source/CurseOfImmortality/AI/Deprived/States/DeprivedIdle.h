// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "DeprivedIdle.generated.h"

class UDeprivedStateMachine;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UDeprivedIdle : public UState
{
	GENERATED_BODY()

public:
	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;
	
private:
	UPROPERTY()
	UDeprivedStateMachine* Controller;
};
