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

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMolochStateMachine* StateMachine;
	UPROPERTY(EditAnywhere)
	USceneComponent* HeadLocation;

	UPROPERTY(EditAnywhere, Category="Base Stats")
	float ChargeAttackCoolDown = 0.5f;
	float CurrentChargeAttackCoolDown;

	//Ranges
	UPROPERTY(EditAnywhere)
	float TriggerRange = 1000.f;
};
