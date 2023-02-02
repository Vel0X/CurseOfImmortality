// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "StormCallerBaseState.generated.h"

class AStormCallerPawn;
class UStormCallerStateMachine;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UStormCallerBaseState : public UState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	AStormCallerPawn* SelfRef  = nullptr;
	UPROPERTY()
	ABaseCharacter* Player = nullptr;
	UPROPERTY()
	UStormCallerStateMachine* Controller = nullptr;
};
