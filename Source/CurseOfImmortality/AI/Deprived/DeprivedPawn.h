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

	virtual void OnDeath() override;

public:
	ADeprivedPawn();

	UFUNCTION(BlueprintCallable)
	void ToggleJumpAttackDamage();

	UPROPERTY(BlueprintReadWrite)
	bool AnimationEnd;

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

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* JumpAttackSphere;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* NormalAttackSphereLeft;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* NormalAttackSphereRight;
	TArray<USphereComponent*> NormalAttackSphereArray;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDeprivedStateMachine* StateMachine;

	//Base Stats
	UPROPERTY(EditDefaultsOnly, Category="Base Stats")
	float DamageJumpAttack = 50.f;
	UPROPERTY(EditDefaultsOnly, Category="Base Stats")
	float DamageNormalAttack = 10.f;

	//Jump Attack
	UPROPERTY(EditDefaultsOnly, Category="Jump Attack")
	float JumpAttackSpeed = 2000.f;
	UPROPERTY(EditDefaultsOnly, Category="Jump Attack")
	float DistJumpAttack = 800.f;
	UPROPERTY(EditDefaultsOnly, Category="Jump Attack")
	float DistAfterPlayer = 200.f;
	UPROPERTY(EditDefaultsOnly, Category="Jump Attack")
	float PlayerForwardVector = 300.f;
	UPROPERTY(EditDefaultsOnly, Category="Jump Attack")
	float JumpAttackCoolDown = 5.f;
	float CurrentJumpAttackCoolDown;

	//Cool Downs and Durations
	UPROPERTY(EditDefaultsOnly, Category="time")
	float RecoverDuration = 2.f;
	float CurrentRecoverDuration;

	//Distances for Movement
	UPROPERTY(EditDefaultsOnly, Category="Distances")
	float DistRunning = 1000.f;
	UPROPERTY(EditDefaultsOnly, Category="Distances")
	float DistNormalAttack = 400.f;
	UPROPERTY(EditDefaultsOnly, Category="Distances")
	float MinDistNormalAttack = 50.f;
};
