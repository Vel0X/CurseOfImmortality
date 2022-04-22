// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "DeprivedPawn.generated.h"

class UDeprivedStateMachine;
class USphereComponent;
class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ADeprivedPawn : public ABaseEnemyPawn
{
	GENERATED_BODY()
public:
	ADeprivedPawn();

	USphereComponent* GetAttackSphere() const;
	
	
private:
	//States
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool Running = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool Jump = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool Stunned = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool Recover = false;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool HitPlayer = false;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* AttackSphere;
	UPROPERTY()
	UDeprivedStateMachine* StateMachine;
	

public:
	bool IsHitPlayer() const;
	void SetHitPlayer(const bool bHitPlayer);
	bool IsRecover() const;
	void SetRecover(const bool bStandUp);
	bool IsIdle() const;
	void SetIdle(const bool bIdle);
	bool IsRunning() const;
	void SetRunning(const bool bMoving);
	bool IsJump() const;
	void SetJump(const bool bJump);
	bool IsStunned() const;
	void SetStunned(const bool bStunned);
};
