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

	virtual void DealDamage(float Damage, ABaseCharacter* EnemyCharacter) override;
	UFUNCTION(BlueprintCallable)
	void ToggleDashEffect();

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
	bool Dead = false;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* JumpAttackSphere;
	UPROPERTY(EditAnywhere)
	USphereComponent* NormalAttackSphereLeft;
	UPROPERTY(EditAnywhere)
	USphereComponent* NormalAttackSphereRight;
	TArray<USphereComponent*> NormalAttackSphereArray;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDeprivedStateMachine* StateMachine;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* DashEffect;

	//Base Stats
	UPROPERTY(EditAnywhere, Category="Base Stats")
	float DamageJumpAttack = 50.f;
	UPROPERTY(EditAnywhere, Category="Base Stats")
	float DamageNormalAttack = 10.f;

	//Jump Attack
	UPROPERTY(EditAnywhere, Category="Jump Attack")
	float JumpAttackSpeed = 2000.f;
	UPROPERTY(EditAnywhere, Category="Jump Attack")
	float DistJumpAttack = 800.f;
	UPROPERTY(EditAnywhere, Category="Jump Attack")
	float DistAfterPlayer = 200.f;
	UPROPERTY(EditAnywhere, Category="Jump Attack")
	float PlayerForwardVector = 300.f;
	UPROPERTY(EditAnywhere, Category="Jump Attack")
	float JumpAttackCoolDown = 5.f;
	float CurrentJumpAttackCoolDown;
	UPROPERTY(EditAnywhere, Category="Jump Attack")
	float JumpAttackChargeTime = 1.f;
	float CurrentJumpAttackChargeTime;
	UPROPERTY(EditAnywhere, Category="Jump Attack")
	float JumpAttackDuration = 2.3f;
	float CurrentJumpAttackDuration;

	//Cool Downs and Durations
	UPROPERTY(EditAnywhere, Category="time")
	float RecoverDuration = 2.f;
	float CurrentRecoverDuration;
	UPROPERTY(EditAnywhere, Category="Time")
	float NormalAttackDuration = 4.29f;
	float CurrentNormalAttackDuration;

	//Distances for Movement
	UPROPERTY(EditAnywhere, Category="Distances")
	float DistRunning = 1000.f;
	UPROPERTY(EditAnywhere, Category="Distances")
	float DistNormalAttack = 400.f;
	UPROPERTY(EditAnywhere, Category="Distances")
	float MinDistNormalAttack = 50.f;
};
