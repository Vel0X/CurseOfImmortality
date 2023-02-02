// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "MolochPawn.generated.h"

class UMolochStateMachine;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AMolochPawn : public ABaseEnemyPawn
{
	GENERATED_BODY()

public:
	AMolochPawn();

	UFUNCTION(BlueprintCallable)
	void ToggleChargeAttack();
	UFUNCTION(BlueprintCallable)
	void ToggleKick();
	UFUNCTION(BlueprintCallable)
	void SpawnStomping();
	UFUNCTION(BlueprintCallable)
	void GetLocation();

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMolochStateMachine* StateMachine;
	UPROPERTY(EditAnywhere)
	USceneComponent* HeadLocation = nullptr;
	UPROPERTY(EditAnywhere)
	USceneComponent* BackLocation = nullptr;
	UPROPERTY(EditAnywhere)
	USceneComponent* StompLocation = nullptr;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* HeadAttack = nullptr;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* BackAttack = nullptr;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* BodyCollision = nullptr;

	FVector TargetLocation = FVector::Zero();

	UPROPERTY(EditAnywhere, Category="Base Stats")
	float ChargeAttackCoolDown = 10.f;
	float CurrentChargeAttackCoolDown = 0.f;
	UPROPERTY(EditAnywhere, Category="Base Stats")
	float AttackDelay = 1.f;
	float CurrentAttackDelay = 0.f;

	//Ranges
	UPROPERTY(EditAnywhere)
	float TriggerRange = 1000.f;
	UPROPERTY(EditAnywhere)
	float ChargeRange = 600.f;
	UPROPERTY(EditAnywhere)
	float AttackRange = 300.f;

	UPROPERTY(BlueprintReadWrite)
	bool AnimationEnd;
	
	//Sates
	UPROPERTY(BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite)
	bool ChargedAttack = false;
	UPROPERTY(BlueprintReadWrite)
	bool NormalAttack = false;
	UPROPERTY(BlueprintReadWrite)
	bool Walking = false;
	UPROPERTY(BlueprintReadWrite)
	bool HitPlayer = false;
	UPROPERTY(BlueprintReadWrite)
	bool HitWall = false;
	UPROPERTY(BlueprintReadWrite)
	bool Stomping = false;
	UPROPERTY(BlueprintReadWrite)
	bool Kick = false;
	UPROPERTY(BlueprintReadWrite)
	bool PrepareCharge = false;
};
