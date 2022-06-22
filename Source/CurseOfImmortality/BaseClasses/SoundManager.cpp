// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"


// Sets default values
ASoundManager::ASoundManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASoundManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	FPersistentWorldManager::SoundManager = this;
}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASoundManager::Play2DSound(const FString& Name)
{
	if(FPersistentWorldManager::GetControlFlag(SFX))
		PlaySoundImpl(Name);
}

void ASoundManager::PlaySoundLocated(const FVector& Position, const FString& Name)
{
	if(FPersistentWorldManager::GetControlFlag(SFX))
		PlaySoundLocatedImpl(Position, Name);
}

void ASoundManager::PlaySoundAttached(const USceneComponent* Component, const FString& Name)
{
	if(FPersistentWorldManager::GetControlFlag(SFX))
		PlaySoundAttachedImpl(Component, Name);
}

USoundWave* ASoundManager::GetSound(FString Name)
{
	return nullptr;
}

