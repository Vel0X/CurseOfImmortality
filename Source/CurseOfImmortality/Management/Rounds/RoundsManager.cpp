// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundsManager.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"


// Sets default values
ARoundsManager::ARoundsManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARoundsManager::BeginPlay()
{
	Super::BeginPlay();
	FPersistentWorldManager::RoundsManager = this;
}

// Called every frame
void ARoundsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(ActiveRound != nullptr)
	{
		ActiveRound->RoundTick(DeltaTime);
	}
}

void ARoundsManager::StartRound(const int Index)
{
	ActiveRound = FPersistentWorldManager::ObjectFactory->GetRound(Index);
	if(ActiveRound != nullptr)
	{
		ActiveRound->BeginRound(true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Round was NULL"));
	}
}

