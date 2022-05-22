// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "MawOfSothrosPawn.generated.h"

class UAbilitySpecification;
class UMawOfSothrosStateMachine;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AMawOfSothrosPawn : public ABaseEnemyPawn
{
	GENERATED_BODY()
public:
	AMawOfSothrosPawn();

	//States
	UPROPERTY(BlueprintReadWrite)
	bool Idle;
	UPROPERTY(BlueprintReadWrite)
	bool Vomit;
	UPROPERTY(BlueprintReadWrite)
	bool TailSweep;
	UPROPERTY(BlueprintReadWrite)
	bool ChargeAttack;
	UPROPERTY(BlueprintReadWrite)
	bool GroundSlam;
	UPROPERTY(BlueprintReadWrite)
	bool Dead;

	UPROPERTY(EditAnywhere)
	UAbilitySpecification* AbilitySpecification;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* VomitUpperJaw;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* VomitLowerJaw;
	UPROPERTY(EditAnywhere)
	USceneComponent* PuddleLowerSpawnLocation;
	UPROPERTY(EditAnywhere)
	USceneComponent* PuddleUpperSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMawOfSothrosStateMachine* StateMachine;

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* MawSmoke;
};
