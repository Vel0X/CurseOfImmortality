// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosBaseState.h"
#include "MawOfSothrosIdle.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UMawOfSothrosIdle : public UMawOfSothrosBaseState
{
	GENERATED_BODY()
	
public:
	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;
};
