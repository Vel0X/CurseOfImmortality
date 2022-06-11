// Fill out your copyright notice in the Description page of Project Settings.


#include "Arena.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"


AArena::AArena()
{
	//PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Gate1 = CreateDefaultSubobject<USceneComponent>("Gate1");
	Gate1->SetupAttachment(RootComponent);
	Gate2 = CreateDefaultSubobject<USceneComponent>("Gate2");
	Gate2->SetupAttachment(RootComponent);
	Gate3 = CreateDefaultSubobject<USceneComponent>("Gate3");
	Gate3->SetupAttachment(RootComponent);
	Gate4 = CreateDefaultSubobject<USceneComponent>("Gate4");
	Gate4->SetupAttachment(RootComponent);
	LargeGate = CreateDefaultSubobject<USceneComponent>("LargeGate");
	LargeGate->SetupAttachment(RootComponent);
	PlayerSpawnPosition = CreateDefaultSubobject<USceneComponent>("PlayerSpawnPosition");
	PlayerSpawnPosition->SetupAttachment(RootComponent);
}

void AArena::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	FPersistentWorldManager::Arena = this;

}

void AArena::BeginPlay()
{
	Super::BeginPlay();
}

//maybe use an array for gates, but might be tricky, since the gates are components
USceneComponent* AArena::GetRandomGate() const
{
	switch (FMath::RandRange(0,4))
	{
	case 0:
		return Gate1;
	case 1:
		return Gate2;
	case 2:
		return Gate3;
	case 3:
		return Gate4;
	case 4:
		return LargeGate;
	default: ;
	}

	return nullptr;
}

