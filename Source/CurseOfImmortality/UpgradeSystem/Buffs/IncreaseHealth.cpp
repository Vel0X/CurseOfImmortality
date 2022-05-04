// Fill out your copyright notice in the Description page of Project Settings.


#include "IncreaseHealth.h"

#include "CurseOfImmortality/UpgradeSystem/GameDummy/Char.h"


// Sets default values for this component's properties
UIncreaseHealth::UIncreaseHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UIncreaseHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UIncreaseHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UIncreaseHealth::OnBuffBegin()
{
	Super::OnBuffBegin();
	static_cast<AChar*>(GetOwner())->RecalculateStats(); //apply the Stat Increase of this Buff
}

void UIncreaseHealth::OnBuffEnd()
{
	Super::OnBuffEnd();
	
}

