// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "DeprivedStateMachine.generated.h"

class ABaseCharacter;
class ADeprivedPawn;
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

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void MoveToTarget(FVector Target, float Speed, float DeltaTime);

	void FocusOnPlayer();

	//Getter and Setter
	ADeprivedPawn* GetSelfRef() const;
	ABaseCharacter* GetPlayer() const;
	UState* GetIdle() const;
	UState* GetRunning() const;
	UState* GetJumpAttack() const;
	UState* GetRecover() const;
	UState* GetHitPlayer() const;
	
protected:
	virtual void BeginPlay() override;

private:
	//References
	UPROPERTY()
	ADeprivedPawn* SelfRef;
	UPROPERTY()
	ABaseCharacter* Player;

	//States
	UPROPERTY()
	UState* Idle;
	UPROPERTY()
	UState* Running;
	UPROPERTY()
	UState* JumpAttack;
	UPROPERTY()
	UState* Recover;
	UPROPERTY()
	UState* HitPlayer;
};
