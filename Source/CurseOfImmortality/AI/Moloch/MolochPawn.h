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

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMolochStateMachine* StateMachine;
	UPROPERTY(EditAnywhere)
	USceneComponent* HeadLocation;
	UPROPERTY(EditAnywhere)
	USceneComponent* BackLocation;
	UPROPERTY(EditAnywhere)
	USceneComponent* StompLocation;
	
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* HeadAttack;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* BackAttack;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* BodyCollision;

	UPROPERTY(EditAnywhere, Category="Base Stats")
	float ChargeAttackCoolDown = 10.f;
	float CurrentChargeAttackCoolDown;
	UPROPERTY(EditAnywhere, Category="Base Stats")
	float AttackDelay = 1.f;
	float CurrentAttackDelay = 0.f;

	//Ranges
	UPROPERTY(EditAnywhere)
	float TriggerRange = 1000.f;
	UPROPERTY(EditAnywhere)
	float ChargeRange = 800.f;
	UPROPERTY(EditAnywhere)
	float AttackRange = 300.f;

	UPROPERTY(BlueprintReadWrite)
	bool AnimationEnd;

	FVector TargetLocation;
};
