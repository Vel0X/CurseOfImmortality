// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuff.h"


// Sets default values for this component's properties
UBaseBuff::UBaseBuff()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UBaseBuff::InitializeBuff(AChar* _Target)
{
	Target = _Target;
}

void UBaseBuff::OnTakeDamage(int AbilityHandle)
{
}

void UBaseBuff::OnBuffBegin()
{
}

void UBaseBuff::OnBuffTick(float DeltaTime)
{
}

void UBaseBuff::OnBuffEnd()
{
}

void UBaseBuff::IntitializeBuff(int Level)
{
}

// Called when the game starts
void UBaseBuff::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

