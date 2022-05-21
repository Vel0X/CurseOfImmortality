// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosBaseState.h"
#include "MawOfSothrosVomit.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CURSEOFIMMORTALITY_API UMawOfSothrosVomit : public UMawOfSothrosBaseState
{
	GENERATED_BODY()

	virtual void OnStateEnter(UStateMachine* StateMachine) override;

	virtual void OnStateExit() override;

	UFUNCTION(BlueprintCallable)
	void ActivateVomit();
	UFUNCTION(BlueprintCallable)
	void DeactivateVomit();
	UFUNCTION(BlueprintCallable)
	void TransitionToIdle();
};