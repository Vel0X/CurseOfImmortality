// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/Moloch/States/MolochBaseState.h"
#include "MolochHitPlayer.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UMolochHitPlayer : public UMolochBaseState
{
	GENERATED_BODY()
	
	virtual void OnStateEnter(UStateMachine* StateMachine) override;
	virtual void OnStateExit() override;
	virtual void OnStateUpdate(float DeltaTime) override;

	FVector TargetLocation;
};
