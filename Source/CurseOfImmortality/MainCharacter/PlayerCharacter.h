// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

class UPlayerAnim;
class UInputManager;
class UAttackManager;
class UStateMachine;

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

protected:
	
	virtual void Setup() override;
	void SetupInputComponent();

public:
	
	virtual void Tick(float DeltaTime) override;
	virtual void ReceiveDamage(float Damage) override;
	virtual void DealDamage(float Damage, ABaseCharacter *EnemyCharacter) override;
	virtual void OnDeath() override;
	
	//States
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Running = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Melee = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Ranged = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Special = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Dash = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Stunned = false;

	//Animation Durations
	UPROPERTY(EditAnywhere, Category="time")
	float MeleeDuration1 = 0.67f;
	UPROPERTY(EditAnywhere, Category="Time")
	float MeleeDuration2 = 0.48;
	UPROPERTY(EditAnywhere, Category="Time")
	float MeleeDuration3 = 1.25;
	UPROPERTY(EditAnywhere, Category="Time")
	float RangedDuration1 = 1.033333f;
	UPROPERTY(EditAnywhere, Category="Time")
	float SpecialDuration1 = 1.066667f;
	UPROPERTY(EditAnywhere, Category="Time")
	float DashDuration1 = 0.3f;

	//Cooldowns
	UPROPERTY(EditAnywhere, Category="Time")
	float DashCooldown = 3;

	UPROPERTY(EditAnywhere, Category="Time")
	float MeleeFollowUpTime = 1;
	
	UPROPERTY(EditAnywhere, Category="Stats")
	float DashSpeed = 2500;
	
	float CurrentAnimationDuration;
	float CurrentDashCooldown;
	float CurrentMeleeFollowUpTime;

	UPROPERTY(BlueprintReadWrite)
	int MeleeComboCount = 0;

	UPROPERTY(BlueprintReadWrite)
	float MeleeStartFrame = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MovementSpeedWhileAttacking = 300;
	
	
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