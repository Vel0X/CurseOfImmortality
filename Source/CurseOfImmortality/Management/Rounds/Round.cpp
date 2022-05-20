// Fill out your copyright notice in the Description page of Project Settings.


#include "Round.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "DataAssets/AssortmentSpecification.h"
#include "DataAssets/RoundSpecification.h"

void URound::BeginRound()
{
	float TotalEnemyWeight = 0.0f;
	float TotalAssortmentWeight = 0.0f;

	for (const auto Tuple : Specification->EnemyWeights)
		TotalEnemyWeight += Tuple.Value;

	for (const auto Tuple : Specification->AssortmentWeights)
		TotalAssortmentWeight += Tuple.Value;

	int CurrentPowerLevel = 0;
	while(CurrentPowerLevel < Specification->TargetPowerlevel)
	{
		const float CurrentPowerLevelRatio = CurrentPowerLevel/Specification->TargetPowerlevel;

		//select new Assortment
		if(CurrentPowerLevelRatio < Specification->AssortmentRatio)
		{
			const float Random = FMath::FRandRange(0.0f, TotalAssortmentWeight);
			EAssortment Assortment = {};
			float CurrentSum = 0.0f;
			for (const auto Tuple : Specification->AssortmentWeights)
			{
				Assortment = Tuple.Key;
				CurrentSum += Tuple.Value;
				
				if(CurrentSum > Random)
					break;
			}

			if(AssortmentsToSpawn.Contains(Assortment))
				AssortmentsToSpawn[Assortment]++;
			else
				AssortmentsToSpawn.Add(Assortment, 1);

			const auto AssortmentSpecification = FPersistentWorldManager::ObjectFactory->GetSpecification(Assortment);
			if(AssortmentSpecification == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Round could not be initialized, because AssortmentSpecificatios was null"));
				return;
			}

			//FIRST instantiate assortment and then retrieve the PowerLevel from it
			CurrentPowerLevel += AssortmentSpecification->PowerLevel; //EnemyPowerLevel
		}

		//select new Enemy
		else
		{
			const float Random = FMath::FRandRange(0.0f, TotalEnemyWeight);
			EEnemy Enemy = {};
			float CurrentSum = 0.0f;
			for (const auto Tuple : Specification->EnemyWeights)
			{
				Enemy = Tuple.Key;
				CurrentSum += Tuple.Value;
				
				if(CurrentSum > Random)
					break;
			}

			if(EnemiesToSpawn.Contains(Enemy))
				EnemiesToSpawn[Enemy]++;
			else
				EnemiesToSpawn.Add(Enemy, 1);

			const auto EnemySpecification = FPersistentWorldManager::ObjectFactory->GetSpecification(Enemy);
			if(EnemySpecification == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Round could not be initialized, because EnemySpecification was null"));
				return;
			}
				
			CurrentPowerLevel += EnemySpecification->PowerLevel; //EnemyPowerLevel
		}
	}
}

void URound::RoundTick(float DeltaTime)
{
	
}

void URound::EndRound()
{
	
}

int URound::CalculateRemainingPowerLevel()
{
	return 0;
}
