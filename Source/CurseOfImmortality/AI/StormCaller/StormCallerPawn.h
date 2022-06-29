// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/AbilitySpecification.h"
#include "StormCallerPawn.generated.h"

class UStormCallerStateMachine;
class URandomAOEAbility;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AStormCallerPawn : public ABaseEnemyPawn
{
	GENERATED_BODY()

public:
	AStormCallerPawn();

	UPROPERTY(EditAnywhere)
	UAbilitySpecification* AbilitySpecification;

	//Sates
	UPROPERTY(BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite)
	bool Attack = false;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStormCallerStateMachine* StateMachine;

	UPROPERTY(EditAnywhere)
	URandomAOEAbility* StormCast;

	//Base Stats
	UPROPERTY(EditAnywhere, Category="Base Stats")
	float AttackCoolDown = 10.f;
	float CurrentAttackCoolDown;

	//Ranges
	UPROPERTY(EditAnywhere, Category="Ranges")
	float AwakeRange = 2000.f;

	virtual bool GetSpawnPosition(FVector& Position, FRotator& Rotation) override;
};
