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
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool NormalAttack = false;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* AttackSphere;
	UPROPERTY()
	UDeprivedStateMachine* StateMachine;

	//Base Stats
	UPROPERTY(EditAnywhere, Category="Base Stats")
	float Speed = 400.f;

	//Cool Downs and Durations
	UPROPERTY(EditAnywhere, Category="time")
	float RecoverDuration = 2.f;
	UPROPERTY(EditAnywhere, Category="Time")
	float CurrentRecoverDuration = RecoverDuration;
	UPROPERTY(EditAnywhere, Category="Time")
	float JumpAttackCoolDown = 10.f;
	UPROPERTY(EditAnywhere, Category="Time")
	float CurrentJumpAttackCoolDown = JumpAttackCoolDown;
	UPROPERTY(EditAnywhere, Category="Time")
	float NormalAttackDuration = 10.f;
	UPROPERTY(EditAnywhere, Category="Time")
	float CurrentNormalAttackDuration = NormalAttackDuration;

	//Distances for Movement
	UPROPERTY(EditAnywhere, Category="Distances")
	float DistJumpAttack = 800.f;
	UPROPERTY(EditAnywhere, Category="Distances")
	float DistRunning = 1000.f;
	UPROPERTY(EditAnywhere, Category="Distances")
	float DistNormalAttack = 400.f;
	UPROPERTY(EditAnywhere, Category="Distances")
	float MinDistNormalAttack = 50.f;
};
