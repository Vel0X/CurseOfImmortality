// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/Moloch/States/MolochBaseState.h"
#include "MolochIdle.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UMolochIdle : public UMolochBaseState
{
	GENERATED_BODY()

	virtual void OnStateEnter(UStateMachine* StateMachine) override;
	virtual void OnStateExit() override;
	virtual void OnStateUpdate(float DeltaTime) override;
};
