// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosBaseState.h"
#include "MawOfSothrosGroundSlam.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UMawOfSothrosGroundSlam : public UMawOfSothrosBaseState
{
	GENERATED_BODY()

	UMawOfSothrosGroundSlam();

	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;
	

};
