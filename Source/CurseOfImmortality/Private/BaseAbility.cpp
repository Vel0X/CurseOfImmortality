// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"

// Sets default values
ABaseAbility::ABaseAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseAbility::BeginPlay()
{
	Super::BeginPlay();
	RemainingAbilityLifetime = AbilityLifetime;
	UE_LOG(LogTemp, Warning, TEXT("AbilityInstance was spawned (Base)"));

}

// Called every frame
void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RemainingAbilityLifetime -= DeltaTime;
	if(RemainingAbilityLifetime <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilityIstance was destroyed (Base)"));
		Destroy();
	}

}

