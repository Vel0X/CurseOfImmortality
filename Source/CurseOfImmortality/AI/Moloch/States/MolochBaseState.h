// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "MolochBaseState.generated.h"

class UMolochStateMachine;
class AMolochPawn;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UMolochBaseState : public UState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	AMolochPawn* SelfRef;
	UPROPERTY()
	ABaseCharacter* Player;
	UPROPERTY()
	UMolochStateMachine* Controller;
};
