// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "InuStateMachine.generated.h"

class ABaseCharacter;
class AInuPawn;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UInuStateMachine : public UStateMachine
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void FocusOnPlayer(float DeltaTime) const;
	bool CheckLineOfSight(FVector Target) const;
	void FindPathToPlayer(TArray<FVector>& Path) const;
	void FindRandomPath(TArray<FVector>& Path, FVector& RandomLocation) const;
	bool FollowPath(TArray<FVector> Path, float DeltaTime, int PathIndex, float RotationSpeed = 360.f,
	                float CurveValue = 1.f) const;
	void MoveToTarget(const FVector Target, const float MovementSpeed, const float DeltaTime,
	                  const float RotationSpeed = 360.f) const;
	void FocusOnLocation(FVector Location, float DeltaTime, float RotationSpeed = 180.f) const;

	//States
	UPROPERTY()
	UState* Idle;
	UPROPERTY()
	UState* Running;
	UPROPERTY()
	UState* RangedAttack;
	UPROPERTY()
	UState* FindStartLocation;
	UPROPERTY()
	UState* Retreat;

	//Getter
	AInuPawn* GetSelfRef() const;
	ABaseCharacter* GetPlayer() const;

protected:
	virtual void BeginPlay() override;

private:
	//References
	UPROPERTY()
	AInuPawn* SelfRef;
	UPROPERTY()
	ABaseCharacter* Player;
};