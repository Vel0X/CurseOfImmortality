// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "DeprivedPawn.generated.h"

class UDeprivedStateMachine;
class USphereComponent;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ADeprivedPawn : public ABaseEnemyPawn
{
	GENERATED_BODY()
// public:
// 	ADeprivedPawn();
// 	virtual void Tick(float DeltaSeconds) override;
//
// protected:
// 	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UDeprivedStateMachine* StateMachine;

	UPROPERTY(EditAnywhere)
	USphereComponent* AttackSphere;
public:
	USphereComponent* GetAttackSphere() const;
private:
	//States
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool Moving = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool Jump = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool Stunned = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool StandUp = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool HitPlayer = false;
public:
	bool IsHitPlayer() const;
	void SetHitPlayer(const bool bHitPlayer);
	bool IsStandUp() const;
	void SetStandUp(const bool bStandUp);
	bool IsIdle() const;
	void SetIdle(const bool bIdle);
	bool IsMoving() const;
	void SetMoving(const bool bMoving);
	bool IsJump() const;
	void SetJump(const bool bJump);
	bool IsStunned() const;
	void SetStunned(const bool bStunned);
};
