// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosBaseState.h"
#include "MawOfSothrosLaser.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UMawOfSothrosLaser : public UMawOfSothrosBaseState
{
	GENERATED_BODY()

	void FireLaser(float DeltaTime);

	virtual void OnStateEnter(UStateMachine* StateMachine) override;
	
	virtual void OnStateExit() override;
	
	virtual void OnStateUpdate(float DeltaTime) override;
	
	FRotator TargetHeadRotation;

	float SpawnFrequency = 0;
};
