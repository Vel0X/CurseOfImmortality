﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "EnemySpecification.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UEnemySpecification : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString DisplayName;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemy> Type;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseEnemyPawn> Class;
	
	UPROPERTY(EditAnywhere)
	int PowerLevel = 0;
};