// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "DeprivedIdle.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UDeprivedIdle : public UState
{
	GENERATED_BODY()
	
	UPROPERTY()
	UStateMachine* Controller;
};
