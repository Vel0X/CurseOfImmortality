// Fill out your copyright notice in the Description page of Project Settings.


#include "Round.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "DataAssets/AssortmentSpecification.h"
#include "DataAssets/RoundSpecification.h"

void URound::SetupRound(URoundSpecification* _Specification)
{
	Specification = _Specification;
}

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
		const float CurrentPowerLevelRatio = (float)(CurrentPowerLevel)/(float)(Specification->TargetPowerlevel);

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

			//UAssortment* AssortmentInstance = FPersistentWorldManager::ObjectFactory->SpawnAssortment(Assortment);
			//CurrentPowerLevel += AssortmentInstance->CalculatePowerLevel();
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

	CurrentStage = 0;
	StageTime = 0.0f;
	RoundPowerLevel = CurrentPowerLevel;
	SpawnsRemaining = true;
	RoundOngoing = true;
	
	if(FPersistentWorldManager::GetLogLevel(Round))
	{
		for (auto Tuple : EnemiesToSpawn)
			UE_LOG(LogTemp, Warning, TEXT("[Enemy] Round contains %i of %s"), Tuple.Value, *FPersistentWorldManager::ObjectFactory->GetSpecification(Tuple.Key)->DisplayName);
		
		for (auto Tuple : AssortmentsToSpawn)
			UE_LOG(LogTemp, Warning, TEXT("[Assortment] Round contains %i of %s"), Tuple.Value, *FPersistentWorldManager::ObjectFactory->GetSpecification(Tuple.Key)->DisplayName);
		
		UE_LOG(LogTemp, Warning, TEXT("Started Round"));
	}

	SpawnEnemies();
}

void URound::RoundTick(float DeltaTime)
{
	//Either the Round has not been started or all enemies are defeated
	if(ActiveEnemies.Num() == 0)
	{
		RoundOngoing = false;
		EndRound();
		return;
	}
	
	if(!SpawnsRemaining)
		return;
	
	StageTime += DeltaTime;
	if(CalculateRemainingPowerLevel() < Specification->PowerLevelTransitionThreshhold[CurrentStage] || StageTime > Specification->TimeTransitionThreshhold[CurrentStage])
	{
		CurrentStage++;
		StageTime = 0.0f;

		SpawnEnemies();
		
		if(CurrentStage >= Specification->Stages)
		{
			//end the Round
			if(FPersistentWorldManager::GetLogLevel(Round))
				UE_LOG(LogTemp, Warning, TEXT("All Enemies of the Round are spawned"));
			
			SpawnsRemaining = false;
		}
		else
		{
			if(FPersistentWorldManager::GetLogLevel(Round))
				UE_LOG(LogTemp, Warning, TEXT("Transitioned into Stage %i"), CurrentStage);
		}
	}
}

void URound::EndRound()
{
	UE_LOG(LogTemp, Warning, TEXT("Round was ended"));
}

void URound::OnEnemyDeath(ABaseEnemyPawn* Enemy)
{
	ActiveEnemies.Remove(Enemy);
}

int URound::CalculateRemainingPowerLevel()
{
	int RemainingPowerLevel = 0;
	for (const auto Enemy : ActiveEnemies)
	{
		if(Enemy != nullptr)
		{
			RemainingPowerLevel += Enemy->PowerLevel;
		}
	}
	return RemainingPowerLevel;
}


void URound::SpawnEnemies()
{
	const int StagePowerLevel = RoundPowerLevel / Specification->Stages;
	int CurrentPowerLevel = 0;
	int CurrentIter = 0;
	constexpr int MaxIter = 100;

	if(FPersistentWorldManager::GetLogLevel(Round))
		UE_LOG(LogTemp, Warning, TEXT("Stage Powerlevel %i"), StagePowerLevel);
	
	//spawn enemies and assortments
	while(CurrentPowerLevel < StagePowerLevel && CurrentIter < MaxIter)
	{
		
		const bool SpawnAssortment = FMath::RandBool();

		if(SpawnAssortment)
		{
			
			if(AssortmentsToSpawn.Num() == 0)
				continue;
			
			const int Rand = FMath::RandRange(0, AssortmentsToSpawn.Num()-1);
			TArray<TEnumAsByte<EAssortment>> Keys;
			AssortmentsToSpawn.GenerateKeyArray(Keys);
			const EAssortment Assortment = Keys[Rand];
			if(AssortmentsToSpawn[Assortment] > 0)
			{
				//Spawn Assortment
				UAssortment* AssortmentInstance = FPersistentWorldManager::ObjectFactory->SpawnAssortment(Assortment);
				TArray<ABaseEnemyPawn*> AssortmentEnemies = AssortmentInstance->SpawnAssortment();
				ActiveEnemies.Append(AssortmentEnemies);
				AssortmentsToSpawn[Assortment] -= 1;
				CurrentPowerLevel += AssortmentInstance->CalculatePowerLevel();
				//AssortmentsToSpawn[Assortment]] -= 1;
			}
		}
		else
		{
			if(EnemiesToSpawn.Num() == 0)
				continue;
			
			const int Rand = FMath::RandRange(0, EnemiesToSpawn.Num()-1);
			TArray<TEnumAsByte<EEnemy>> Keys;
			EnemiesToSpawn.GenerateKeyArray(Keys);
			const EEnemy Enemy = Keys[Rand];
			if(EnemiesToSpawn[Enemy] > 0)
			{
				//Spawn Assortment
				ABaseEnemyPawn* EnemyInstance = FPersistentWorldManager::ObjectFactory->SpawnEnemyCustomSpawnBehaviour(Enemy);
				ActiveEnemies.Add(EnemyInstance);
				EnemiesToSpawn[Enemy] -= 1;
				CurrentPowerLevel += EnemyInstance->PowerLevel;
			}
		}
		CurrentIter++;
	}
}
