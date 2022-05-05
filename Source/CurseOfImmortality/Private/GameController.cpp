// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"

void UGameController::OnStart()
{
	Super::OnStart();
	UE_LOG(LogTemp, Warning, TEXT("GameController was created"));

}

void UGameController::BindAbilityController(AAttackManager* _AttackManager)
{
	UE_LOG(LogTemp, Warning, TEXT("Bind AbilityController was called"));
	AttackManager = _AttackManager;
}

AAttackManager* UGameController::GetAttackManager() const
{
	return AttackManager;
}

void UGameController::BindPathfindingGrid(APathfindingGrid* _PathfindingGrid)
{
	PathfindingGrid = _PathfindingGrid;
}

APathfindingGrid* UGameController::GetPathfindingGrid() const
{
	return PathfindingGrid;
}

TArray<AActor*> UGameController::GetEnemies() const
{
	return ActiveEnemies;
}

void UGameController::AddEnemy(AActor* Enemy)
{
	ActiveEnemies.Add(Enemy);
}
