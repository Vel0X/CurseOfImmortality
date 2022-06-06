// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeprivedBaseState.h"
#include "DeprivedJumpAttack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CURSEOFIMMORTALITY_API UDeprivedJumpAttack : public UDeprivedBaseState
{
	GENERATED_BODY()
	float Time = 0.5f;

public:
	virtual void OnStateEnter(UStateMachine* StateMachine) override;
	
	virtual void OnStateExit() override;

	virtual void OnStateUpdate(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetLocation();

private:
	FVector PlayerLocation;
	FVector JumpDestination;
	FVector JumpDir;
	FVector OwnLocation;

	bool LocationSet = false;

	void Jump(float DeltaTime) const;
};
