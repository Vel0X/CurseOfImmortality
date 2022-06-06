// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterStateMachine.h"
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
	virtual void OnDeath() override;

	//Cooldowns
	UPROPERTY(EditAnywhere, Category="Time")
	float DashCooldown = 1.0f;

	UPROPERTY(EditAnywhere, Category="Time")
	float MeleeFollowUpTime = 0.5;
	
	UPROPERTY(EditAnywhere, Category="Stats")
	float DashSpeed = 4000;
	
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
		UPlayerCharacterStateMachine* StateMachine;
	UPROPERTY(EditAnywhere)
		UPlayerAnim* PlayerAnim;
};