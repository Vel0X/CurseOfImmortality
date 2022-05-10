// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "PlayerCharacter.h"
#include "Engine/GameInstance.h"
#include "GameController.generated.h"

class UAttackManager;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UGameController : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void OnStart() override;
public:
	void BindAbilityController(UAttackManager* _AttackManager);
	void BindPlayerCharacter(APlayerCharacter* _PlayerCharacter);
	UAttackManager* GetAttackManager() const;
	APlayerCharacter* GetPlayerCharacter() const;

	void BindPathfindingGrid(APathfindingGrid* _PathfindingGrid);
	APathfindingGrid* GetPathfindingGrid() const;
	
	TArray<AActor*> GetEnemies() const;
	void AddEnemy(AActor* Enemy);
	
private:
	UPROPERTY(EditAnywhere)
	UAttackManager* AttackManager;

	UPROPERTY(EditAnywhere)
	APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(EditAnywhere)
	APathfindingGrid* PathfindingGrid;
	
	UPROPERTY(EditAnywhere)
	TArray<AActor*> ActiveEnemies;

};
