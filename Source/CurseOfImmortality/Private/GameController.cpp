// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"

void UGameController::OnStart()
{
	Super::OnStart();
	UE_LOG(LogTemp, Warning, TEXT("GameController was created"));

}

void UGameController::BindAbilityController()
{
	UE_LOG(LogTemp, Warning, TEXT("Bind AbilityController was called"));

}
