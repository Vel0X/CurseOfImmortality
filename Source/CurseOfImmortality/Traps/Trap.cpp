// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/Traps/Trap.h"

// Sets default values
ATrap::ATrap()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrap::Setup()
{
	Super::Setup();
}


// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrap::DealDamage(float Damage, ABaseCharacter *EnemyCharacter)
{
	Super::DealDamage(Damage, EnemyCharacter);
}