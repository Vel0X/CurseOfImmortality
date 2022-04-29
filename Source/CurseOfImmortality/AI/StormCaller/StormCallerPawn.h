// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "StormCallerPawn.generated.h"

class UStormCallerStateMachine;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AStormCallerPawn : public ABaseEnemyPawn
{
	GENERATED_BODY()

public:
	AStormCallerPawn();

	//Sates
	UPROPERTY(BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite)
	bool Attack = false;
	UPROPERTY(BlueprintReadWrite)
	bool Dead = false;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStormCallerStateMachine* StateMachine;

	//Base Stats
	UPROPERTY(EditAnywhere, Category="Base Stats")
	float Damage = 10.f;

	//Ranges
	UPROPERTY(EditAnywhere, Category="Ranges")
	float AwakeRange = 1000.f;
	UPROPERTY(EditAnywhere, Category="Ranges")
	float AttackRadius = 800.f;
};