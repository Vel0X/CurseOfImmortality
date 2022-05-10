// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ACustomGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec, Category = ExecFunctions)
	void SpawnEnemy();

	UFUNCTION(Exec, Category = ExecFunctions)
	void AttackManager_PickThreeFromPool() const;

	UFUNCTION(Exec, Category = ExecFunctions)
	void AttackManager_GetUpgrade(int Index) const;

	UFUNCTION(Exec, Category = ExecFunctions)
	void AttackManager_PrintCurrentlyActive() const;
};
