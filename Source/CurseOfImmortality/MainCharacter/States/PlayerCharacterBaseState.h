// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "PlayerCharacterBaseState.generated.h"

class UPlayerCharacterStateMachine;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UPlayerCharacterBaseState : public UState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	APlayerCharacter* SelfRef;
	UPROPERTY()
	UPlayerCharacterStateMachine* Controller;
};
