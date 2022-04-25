// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "DeprivedJumpAttack.generated.h"

class UDeprivedStateMachine;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UDeprivedJumpAttack : public UState
{
	GENERATED_BODY()

public:
	virtual void OnStateEnter(UStateMachine* StateMachine) override;
	
	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;

private:
	UPROPERTY()
	UDeprivedStateMachine* Controller;

	FVector PlayerLocation;
	FVector JumpDestination;
	FVector JumpDir;

	bool LocationSet = false;

	float JumpSpeed = 2000.f;
	const float ChargeTime = 1.f;
	float RemainingTime = ChargeTime;

	void Jump(float DeltaTime);
};
