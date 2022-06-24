// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InuStateMachine.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "InuPawn.generated.h"

class UAbilitySpecification;
UCLASS()
class CURSEOFIMMORTALITY_API AInuPawn : public ABaseEnemyPawn
{
	GENERATED_BODY()

public:
	AInuPawn();

	UFUNCTION(BlueprintCallable)
	void FireProjectile();

	UPROPERTY(EditAnywhere)
	UAbilitySpecification* AbilitySpecification;

	//Sates
	UPROPERTY(BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite)
	bool RangedAttack = false;
	UPROPERTY(BlueprintReadWrite)
	bool Running = false;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInuStateMachine* StateMachine;

	UPROPERTY(EditAnywhere, Category="Base Stats")
	float AttackCoolDown = 0.5f;
	float CurrentAttackCoolDown;

	//Ranges
	float TriggerRange = 1200.f;
	UPROPERTY(EditAnywhere, Category="Ranges")
	float MinRange = 800.f;
	UPROPERTY(EditAnywhere, Category="Ranges")
	float MaxRange = 1100.f;
	UPROPERTY(EditAnywhere, Category="Ranges")
	float AttackRange;
};
