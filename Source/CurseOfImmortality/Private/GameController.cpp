// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"

#include "PlayerCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"

void UGameController::OnStart()
{
	Super::OnStart();
	UE_LOG(LogTemp, Warning, TEXT("GameController was created"));
}

void UGameController::BindAbilityController(UAttackManager* _AttackManager)
{
	UE_LOG(LogTemp, Warning, TEXT("Bind AbilityController was called"));
	AttackManager = _AttackManager;
}

void UGameController::BindPlayerCharacter(APlayerCharacter* _PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Bind PlayerCharacter was called"));
	PlayerCharacter = _PlayerCharacter;
}

UAttackManager* UGameController::GetAttackManager() const
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
