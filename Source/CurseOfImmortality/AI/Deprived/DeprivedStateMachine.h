// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeprivedPawn.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "DeprivedStateMachine.generated.h"

class UDeprivedRunning;
class UDeprivedIdle;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UDeprivedStateMachine : public UStateMachine
{
	GENERATED_BODY()
public:
	UDeprivedStateMachine();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveToTarget(FVector Target, float Speed, float DeltaTime);

	void FocusOnPlayer();
	
	ADeprivedPawn* GetSelfRef() const;
	ABaseCharacter* GetPlayer() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ADeprivedPawn* SelfRef;

	UPROPERTY()
	ABaseCharacter* Player;

	UPROPERTY()
	TSubclassOf<UDeprivedIdle> Idle;
	UPROPERTY()
	UDeprivedRunning* Running;
};