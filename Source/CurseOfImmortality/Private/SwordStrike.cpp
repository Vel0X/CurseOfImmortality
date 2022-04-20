// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordStrike.h"

void ASwordStrike::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AbilityInstance was spawned (Child)"));

}

// Called every frame
void ASwordStrike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}