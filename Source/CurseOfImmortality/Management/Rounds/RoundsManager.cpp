// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundsManager.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"


ARoundsManager::ARoundsManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARoundsManager::BeginPlay()
{
	UE_LOG(LogTemp, Error, TEXT("BeginPlay"));
	Super::BeginPlay();

	if(FPersistentWorldManager::GetControlFlag(AutomaticRoundIncrement))
	{
		StartRound(CurrentRoundIndex);
	}
}

void ARoundsManager::Restart()
{
	if(ActiveRound != nullptr)
		ActiveRound->EndRound(); //clear all the enemies from the current round

	CurrentRoundIndex = 0;
}


void ARoundsManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//UE_LOG(LogTemp, Error, TEXT("PostInitComponents"));

	FPersistentWorldManager::RoundsManager = this;

	/*
	if(GetWorld())
	{
		if(GetWorld()->WorldType == EWorldType::Game)
		{
			UE_LOG(LogTemp, Error, TEXT("%s - PostInitProperties=Game"), *GetName());
		}
		if(GetWorld()->WorldType == EWorldType::PIE)
		{
			UE_LOG(LogTemp, Error, TEXT("%s - PostInitProperties=PlayInEditor"), *GetName());
		}
		if(GetWorld()->WorldType == EWorldType::Editor)
		{
			UE_LOG(LogTemp, Error, TEXT("%s - PostInitProperties=Editor"), *GetName());
		}
	}
	*/
}

void ARoundsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(ActiveRound != nullptr)
	{
		if(ActiveRound->RoundOngoing)
		{
			ActiveRound->RoundTick(DeltaTime);
		}
		else
		{
			ActiveRound->ConditionalBeginDestroy();
			if(FPersistentWorldManager::GetControlFlag(AutomaticRoundIncrement))
			{
				CurrentRoundIndex++;
				StartRound(CurrentRoundIndex);
			}
		}
	}
}

void ARoundsManager::StartRound(const int Index)
{
	UE_LOG(LogTemp, Error, TEXT("Trying to Start Round %i"), Index);

	if(!FPersistentWorldManager::ObjectFactory)
	{
		UE_LOG(LogTemp, Error, TEXT("NEED TO FIX ORDER OF INITIALIZATION"));
		return;
	}
	ActiveRound = FPersistentWorldManager::ObjectFactory->GetRound(Index);
	if(ActiveRound != nullptr)
	{
		ActiveRound->BeginRound();
		CurrentRoundIndex = Index;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Round was NULL"));
	}

}

void ARoundsManager::OnEnemyDied(ABaseEnemyPawn* Enemy) const
{
	if(ActiveRound != nullptr)
	{
		ActiveRound->OnEnemyDeath(Enemy);
	}
}