// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

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
	
	void SetupPlayerInputComponent();

	void MoveForward(float Value);

	void MoveRight(float Value);

public:

	virtual void Tick(float DeltaTime) override;
	
//	virtual void TakeDamage(float Damage) override;

//	virtual void DoDamage(float Damage, ABaseCharacter EnemyCharacter) override;

//	virtual void OnDeath() override;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera;

	FVector MoveInput;
	float Yaw;
};