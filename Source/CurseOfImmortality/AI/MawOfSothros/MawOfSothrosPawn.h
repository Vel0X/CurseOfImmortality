// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "MawOfSothrosPawn.generated.h"

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
	UNiagaraComponent* VomitUpperJaw;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* VomitLowerJaw;

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UMawOfSothrosStateMachine* StateMachine;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* MawSmoke;
};