// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
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

protected:
	
	virtual void Setup() override;
	
	void SetupInputComponent();
	//void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override; TODO

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
	
};