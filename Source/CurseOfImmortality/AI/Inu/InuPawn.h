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

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileLocation = nullptr;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* Aura= nullptr;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh= nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInuStateMachine* StateMachine= nullptr;
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* DeathParticle= nullptr;

	//Sates
	UPROPERTY(BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite)
	bool RangedAttack = false;
	UPROPERTY(BlueprintReadWrite)
	bool Running = false;
	UPROPERTY(BlueprintReadWrite)
	bool Emerge = false;

	UPROPERTY(BlueprintReadWrite)
	bool AnimationStart = false;
	UPROPERTY(BlueprintReadWrite)
	bool AnimationEnd = false;
	bool SpawnedByMaw = false;

	UPROPERTY(EditAnywhere, Category="Base Stats")
	float AttackCoolDown = 0.5f;
	float CurrentAttackCoolDown = 0.f;

	//Ranges
	float TriggerRange = 1000.f;
	UPROPERTY(EditAnywhere, Category="Ranges")
	float MinRange = 600.f;
	UPROPERTY(EditAnywhere, Category="Ranges")
	float MaxRange = 800.f;
	UPROPERTY(EditAnywhere, Category="Ranges")
	float AttackRange = 600.f;
};
