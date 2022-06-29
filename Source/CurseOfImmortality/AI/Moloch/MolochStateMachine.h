// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "MolochStateMachine.generated.h"

class AMolochPawn;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UMolochStateMachine : public UStateMachine
{
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	TArray<FHitResult> GetHitsInLine(FVector Target) const;
	bool CheckLineOfSight(FVector Target) const;
	void FindPathToPlayer(TArray<FVector>& Path) const;
	void FindRandomPath(TArray<FVector>& Path, FVector& RandomLocation) const;
	bool FollowPath(TArray<FVector> Path, float DeltaTime, int PathIndex, bool IgnoreWall = false,
	                float RotationSpeed = 90.f,
	                float CurveValue = 1.f) const;

	void MoveToTarget(const FVector Target, const float MovementSpeed, const float DeltaTime,
	                  const float RotationSpeed = 90.f, bool IgnoreAllCol = false, bool IgnorePawns = false) const;

	void FocusOnLocation(FVector Location, float DeltaTime, float RotationSpeed = 90.f) const;
	float CalculateAngleBetweenVectors(FVector VectorOne, FVector VectorTwo) const;

	//States
	UPROPERTY()
	UState* Idle;
	UPROPERTY()
	UState* Walking;
	UPROPERTY()
	UState* ChargeAttack;
	UPROPERTY(BlueprintReadOnly)
	UState* NormalAttack;
	UPROPERTY()
	UState* HitPlayer;
	UPROPERTY()
	UState* HitWall;
	UPROPERTY()
	UState* FindStartLocation;
	UPROPERTY()
	UState* Stomping;
	UPROPERTY()
	UState* Kick;
	UPROPERTY()
	UState* PrepareCharge;

	//Getter
	AMolochPawn* GetSelfRef() const;
	APlayerCharacter* GetPlayer() const;

protected:
	virtual void BeginPlay() override;
	//References
	UPROPERTY()
	AMolochPawn* SelfRef;
	UPROPERTY()
	APlayerCharacter* Player;

	float Offset = 200.f;
};
