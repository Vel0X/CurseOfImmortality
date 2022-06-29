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

	UFUNCTION(BlueprintCallable)
	void ToggleJumpAttackDamage();

	UFUNCTION(BlueprintCallable)
	void ToggleLeftHand();

	UFUNCTION(BlueprintCallable)
	void ToggleRightHand();

	UFUNCTION(BlueprintCallable)
	void ToggleHandVFX();

	UPROPERTY(BlueprintReadWrite)
	bool AnimationEnd;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool WeakDeprived = true;

	//States
	UPROPERTY(BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite)
	bool Running = false;
	UPROPERTY(BlueprintReadWrite)
	bool Jump = false;
	UPROPERTY(BlueprintReadWrite)
	bool Stunned = false;
	UPROPERTY(BlueprintReadWrite)
	bool Recover = false;
	UPROPERTY(BlueprintReadWrite)
	bool HitPlayer = false;
	UPROPERTY(BlueprintReadWrite)
	bool NormalAttack = false;
	UPROPERTY(BlueprintReadWrite)
	bool FrenziedAttack = false;
	UPROPERTY(BlueprintReadWrite)
	bool Feast = false;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* JumpAttackSphere;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* AttackSphereLeft;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* AttackSphereRight;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* HandGlowLeft;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* HandGlowRight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDeprivedStateMachine* StateMachine;

	//Base Stats
	UPROPERTY(EditDefaultsOnly, Category="Base Stats")
	float FrenziedAttackCoolDown = 10.f;
	float CurrentFrenziedAttackCoolDown;
	
	//Jump Attack
	UPROPERTY(EditDefaultsOnly, Category="Jump Attack")
	float JumpAttackSpeed = 2000.f;
	UPROPERTY(EditDefaultsOnly, Category="Jump Attack")
	float DistJumpAttack = 800.f;
	UPROPERTY(EditDefaultsOnly, Category="Jump Attack")
	float JumpAttackCoolDown = 5.f;
	float CurrentJumpAttackCoolDown;

	//Cool Downs and Durations
	UPROPERTY(EditDefaultsOnly, Category="Time")
	float RecoverDuration = 2.f;
	float CurrentRecoverDuration;

	//Distances for Movement
	UPROPERTY(EditDefaultsOnly, Category="Distances")
	float DistRunning = 1000.f;
	UPROPERTY(EditDefaultsOnly, Category="Distances")
	float DistFrenziedAttack = 400.f;
	UPROPERTY(EditDefaultsOnly, Category="Distances")
	float DistNormalAttack = 200.f;
	UPROPERTY(EditDefaultsOnly, Category="Distances")
	float MinDistFrenziedAttack = 200.f;
};
