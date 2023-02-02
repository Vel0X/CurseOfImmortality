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

	virtual bool GetSpawnPosition(FVector& Position, FRotator& Rotation) override;

	UPROPERTY(EditAnywhere)
	UAbilitySpecification* AbilitySpecification = nullptr;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStormCallerStateMachine* StateMachine = nullptr;
	UPROPERTY(EditAnywhere)
	URandomAOEAbility* StormCast = nullptr;

	//Base Stats
	UPROPERTY(EditAnywhere, Category="Base Stats")
	float AttackCoolDown = 10.f;
	float CurrentAttackCoolDown = 0.f;

	//Ranges
	UPROPERTY(EditAnywhere, Category="Ranges")
	float AwakeRange = 2000.f;

	//Sates
	UPROPERTY(BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite)
	bool Attack = false;
};
