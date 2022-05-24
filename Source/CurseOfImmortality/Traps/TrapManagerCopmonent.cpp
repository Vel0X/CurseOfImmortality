// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/Traps/TrapManagerCopmonent.h"

// Sets default values for this component's properties
UTrapManagerCopmonent::UTrapManagerCopmonent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTrapManagerCopmonent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTrapManagerCopmonent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTrapManagerCopmonent::UpgradeTrapsOfType(TEnumAsByte<ETrapTypes> Type)
{
	UpgradeTraptype.Broadcast(Type, 0);
}
void UTrapManagerCopmonent::ActivateAllTrapsOfType(TEnumAsByte<ETrapTypes> Type)
{
	ActivateTrapsOfType.Broadcast(Type, 0);
}

void UTrapManagerCopmonent::DeactivateAllTrapsOfType(TEnumAsByte<ETrapTypes> Type)
{
	DeactivateTrapsOfType.Broadcast(Type, 0);
}



