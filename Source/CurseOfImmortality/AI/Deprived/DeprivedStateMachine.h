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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	TArray<FHitResult> GetHitsInLine(FVector Target) const;
	bool CheckLineOfSight(FVector Target) const;
	void FindPathToPlayer(TArray<FVector>& Path) const;
	void FindRandomPath(TArray<FVector>& Path, FVector& RandomLocation) const;
	bool FollowPath(TArray<FVector> Path, float DeltaTime, int PathIndex, float RotationSpeed = 360.f,
	                float CurveValue = 1.f) const;

	void MoveToTarget(const FVector Target, const float MovementSpeed, const float DeltaTime,
	                  const float RotationSpeed = 360.f, bool IgnoreAllCol = false) const;

	void FocusOnLocation(FVector Location, float DeltaTime, float RotationSpeed = 180.f) const;

	//States
	UPROPERTY()
	UState* Idle = nullptr;
	UPROPERTY()
	UState* Running = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UState* JumpAttack = nullptr;
	UPROPERTY()
	UState* Recover = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UState* NormalAttack = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UState* FrenziedAttack = nullptr;
	UPROPERTY()
	UState* FindStartLocation = nullptr;
	UPROPERTY()
	UState* Feast = nullptr;
	
	FVector LastLocation = FVector::Zero();
	
	bool StateChanged = false;

	//Getter
	ADeprivedPawn* GetSelfRef() const;
	APlayerCharacter* GetPlayer() const;

protected:
	virtual void BeginPlay() override;
	//References
	UPROPERTY()
	ADeprivedPawn* SelfRef = nullptr;
	UPROPERTY()
	APlayerCharacter* Player = nullptr;

	float Offset = 200.f;
};
