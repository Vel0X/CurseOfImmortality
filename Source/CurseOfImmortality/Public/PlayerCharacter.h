// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

class UAttackManager;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

	//States
	UPROPERTY(BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite)
	bool Running = false;
	UPROPERTY(BlueprintReadWrite)
	bool Melee = false;
	UPROPERTY(BlueprintReadWrite)
	bool Ranged = false;
	UPROPERTY(BlueprintReadWrite)
	bool Special = false;
	UPROPERTY(BlueprintReadWrite)
	bool Dash = false;
	UPROPERTY(BlueprintReadWrite)
	bool Stunned = false;

	//Animation Durations
	UPROPERTY(EditAnywhere, Category="time")
	float MeleeDuration1 = 2.4f;
	UPROPERTY(EditAnywhere, Category="Time")
	float MeleeDuration2 = 0;
	UPROPERTY(EditAnywhere, Category="Time")
	float MeleeDuration3 = 0;
	UPROPERTY(EditAnywhere, Category="Time")
	float RangedDuration1 = 1.033333f;
	UPROPERTY(EditAnywhere, Category="Time")
	float SpecialDuration1 = 1.066667f;
	UPROPERTY(EditAnywhere, Category="Time")
	float DashDuration1 = 0.3f;
	
	float CurrentAnimationDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MovementSpeedWhileAttacking = 300;
	
protected:
	
	virtual void Setup() override;
	
	void SetupInputComponent();

public:
	
	virtual void Tick(float DeltaTime) override;
	virtual void ReceiveDamage(float Damage) override;
	virtual void DealDamage(float Damage, ABaseCharacter *EnemyCharacter) override;
	virtual void OnDeath() override;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera;
	UPROPERTY(EditAnywhere)
		UInputManager* InputManager;
	UPROPERTY(EditAnywhere)
		UAttackManager* AttackManager;
	UPROPERTY(EditAnywhere)
		UStateMachine* StateMachine;
	
};