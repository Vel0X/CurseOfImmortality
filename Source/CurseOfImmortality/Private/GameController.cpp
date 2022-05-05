// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
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

UAttackManager* UGameController::GetAttackManager() const
{
	return AttackManager;
}

TArray<AActor*> UGameController::GetEnemies() const
{
	return ActiveEnemies;
}

void UGameController::AddEnemy(AActor* Enemy)
{
	ActiveEnemies.Add(Enemy);
}

AMainChar* UGameController::GetMainChar() const
{
	return MainChar;
}

void UGameController::SetMainChar(AMainChar* _MainChar)
{
	MainChar = _MainChar;
}
