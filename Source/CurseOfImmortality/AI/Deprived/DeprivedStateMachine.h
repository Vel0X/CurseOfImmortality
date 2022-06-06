// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "DeprivedStateMachine.generated.h"

class APlayerCharacter;
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

	void MoveToTarget(FVector Target, float Speed, float DeltaTime) const;

	void FocusOnLocation(FVector Location, float DeltaTime) const;
	// void FocusOnPath(FVector PathLocation, float DeltaTime) const;

	//States
	UPROPERTY()
	UState* Idle;
	UPROPERTY()
	UState* Running;
	UPROPERTY(BlueprintReadOnly)
	UState* JumpAttack;
	UPROPERTY()
	UState* Recover;
	UPROPERTY()
	UState* HitPlayer;
	UPROPERTY(BlueprintReadOnly)
	UState* NormalAttack;
	UPROPERTY()
	UState* FindStartLocation;

	//Getter
	ADeprivedPawn* GetSelfRef() const;
	APlayerCharacter* GetPlayer() const;

protected:
	virtual void BeginPlay() override;

private:
	//References
	UPROPERTY()
	ADeprivedPawn* SelfRef;
	UPROPERTY()
	APlayerCharacter* Player;
};
