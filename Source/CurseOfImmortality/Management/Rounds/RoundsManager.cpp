// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundsManager.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"


ARoundsManager::ARoundsManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARoundsManager::BeginPlay()
{
	Super::BeginPlay();


}

void ARoundsManager::Restart()
{
	if(ActiveRound != nullptr)
		ActiveRound->EndRound(); //clear all the enemies from the current round

	CurrentRoundIndex = -1;
	FPersistentWorldManager::PlayerCharacter->Respawn();
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
	if(InitializationPending > 0)
		--InitializationPending;
	
	if(InitializationPending == 0)
	{
		InitializationPending = -1;
		if(FPersistentWorldManager::GetControlFlag(AutomaticRoundIncrement) || AutoRoundIncrement)
		{
			StartRound(CurrentRoundIndex);
		}
	}
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
			if(FPersistentWorldManager::GetControlFlag(AutomaticRoundIncrement) || AutoRoundIncrement)
			{
				CurrentRoundIndex++;
				UE_LOG(LogTemp, Error, TEXT("RI %i"), CurrentRoundIndex);
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
		FPersistentWorldManager::GameMode->ShowCredits();
		UE_LOG(LogTemp, Error, TEXT("Round was NULL"));
	}

}

void ARoundsManager::EndCurrentRound()
{
	if(ActiveRound != nullptr)
	{
		ActiveRound->EndRound();
	}
}

void ARoundsManager::OnEnemyDied(ABaseEnemyPawn* Enemy) const
{
	if(ActiveRound != nullptr)
	{
		ActiveRound->OnEnemyDeath(Enemy);
	}
}
