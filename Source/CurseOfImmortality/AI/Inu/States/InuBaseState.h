// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "InuBaseState.generated.h"

class UInuStateMachine;
class AInuPawn;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UInuBaseState : public UState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	AInuPawn* SelfRef;
	UPROPERTY()
	ABaseCharacter* Player;
	UPROPERTY()
	UInuStateMachine* Controller;
};
