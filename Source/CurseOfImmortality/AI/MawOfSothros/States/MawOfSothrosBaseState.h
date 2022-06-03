// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "MawOfSothrosBaseState.generated.h"

class AMawOfSothrosPawn;
class UMawOfSothrosStateMachine;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UMawOfSothrosBaseState : public UState
{
	GENERATED_BODY()

public:
	int Weight = 100;
	EMawAttacks AttackType;

protected:
	UPROPERTY()
	AMawOfSothrosPawn* SelfRef;
	UPROPERTY()
	APlayerCharacter* Player;
	UPROPERTY()
	UMawOfSothrosStateMachine* Controller;
};
