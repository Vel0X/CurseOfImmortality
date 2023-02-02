// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "DeprivedBaseState.generated.h"

class UDeprivedStateMachine;
class ADeprivedPawn;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UDeprivedBaseState : public UState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ADeprivedPawn* SelfRef = nullptr;
	UPROPERTY()
	APlayerCharacter* Player = nullptr;
	UPROPERTY()
	UDeprivedStateMachine* Controller = nullptr;
};
