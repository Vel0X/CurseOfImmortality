// Fill out your copyright notice in the Description page of Project Settings.


#include "Assortment.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/Management/Rounds/DataAssets/AssortmentSpecification.h"

TArray<ABaseEnemyPawn*> UAssortment::SpawnAssortment()
{
	TArray<ABaseEnemyPawn*> Enemies;
	for (auto Tuple : EnemiesMap)
	{
		for (int i = 0; i < Tuple.Value; ++i)
		{
			Enemies.Add(FPersistentWorldManager::ObjectFactory->SpawnEnemyCustomSpawnBehaviour(Tuple.Key));
		}
	}
	return Enemies;
}

void UAssortment::Initialize(const UAssortmentSpecification* AssortmentSpecification)
{
	EnemiesMap = AssortmentSpecification->Enemies;
}

void UAssortment::Determine()
{
}

int UAssortment::CalculatePowerLevel()
{
	int PowerLevel = 0;
	for (auto Tuple : EnemiesMap)
	{
		PowerLevel += FPersistentWorldManager::ObjectFactory->GetSpecification(Tuple.Key)->PowerLevel * Tuple.Value;
	}
	return PowerLevel;
}
