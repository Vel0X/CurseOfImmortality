// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "MawOfSothrosStateMachine.generated.h"

class APlayerCharacter;
class AMawOfSothrosPawn;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UMawOfSothrosStateMachine : public UStateMachine
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void MoveToTarget(FVector Target, float Speed, float DeltaTime);
	void FocusOnPlayer(float DeltaTime, float Speed) const;

	float CalculateAngleBetweenVectors(FVector VectorOne, FVector VectorTwo) const;

	//States
	UPROPERTY()
	UState* Idle;
	UPROPERTY(BlueprintReadOnly)
	UState* Vomit;
	UPROPERTY()
	UState* GroundSlam;
	UPROPERTY()
	UState* ChargeAttack;
	UPROPERTY()
	UState* TailSweep;

	//Getter
	AMawOfSothrosPawn* GetSelfRef() const;
	APlayerCharacter* GetPlayer() const;

protected:
	virtual void BeginPlay() override;

private:
	//References
	UPROPERTY()
	AMawOfSothrosPawn* SelfRef;
	UPROPERTY()
	APlayerCharacter* Player;
};
