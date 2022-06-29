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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMolochStateMachine* StateMachine;
	UPROPERTY(EditAnywhere)
	USceneComponent* HeadLocation;
	UPROPERTY(EditAnywhere)
	USceneComponent* BackLocation;
	
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* HeadAttack;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* BodyCollision;

	UPROPERTY(EditAnywhere, Category="Base Stats")
	float ChargeAttackCoolDown = 20.f;
	float CurrentChargeAttackCoolDown;

	//Ranges
	UPROPERTY(EditAnywhere)
	float TriggerRange = 1000.f;
	UPROPERTY(EditAnywhere)
	float ChargeRange = 800.f;
	UPROPERTY(EditAnywhere)
	float AttackRange = 300.f;
	
	UPROPERTY(BlueprintReadWrite)
	bool AnimationEnd;
};
