// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/Traps/TrapManagerCopmonent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

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
	FPersistentWorldManager::TrapManager = this;
	sawLvl = 0;
	arrowLvl = 0;
	turretLvl = 0;
	spikesLvl = 0;

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
	UpgradeTraptype.Broadcast(Type, GetLvl(Type));
}
void UTrapManagerCopmonent::ActivateAllTrapsOfType(TEnumAsByte<ETrapTypes> Type)
{
	ActivateTrapsOfType.Broadcast(Type, GetLvl(Type));
}

void UTrapManagerCopmonent::DeactivateAllTrapsOfType(TEnumAsByte<ETrapTypes> Type)
{
	DeactivateTrapsOfType.Broadcast(Type, GetLvl(Type));
}

void UTrapManagerCopmonent::ChooseRandomDowngrade()
{
	for (int i = 0; i < 1000; i++)
	{
		int rnd = FMath::RandRange(1,4);

		switch (rnd)
		{
		case 1:
			if(arrowLvl < 3)
			{
				arrowLvl++;
				UpgradeTrapsOfType(ETrapTypes::Arrows);
				return;
			} 			
			break;
		case 2:
			if(spikesLvl < 3)
			{
				spikesLvl++;
				UpgradeTrapsOfType(ETrapTypes::Spikes);
				return;
			}
			break;
		case 3:
			if(sawLvl < 3)
			{
				sawLvl++;
				UpgradeTrapsOfType(ETrapTypes::Saws);
				return;
			}
			break;
		case 4:
			if(turretLvl < 3)
			{
				turretLvl++;
				UpgradeTrapsOfType(ETrapTypes::Turrets);
				return;
			}
			break;
		}
	}
	
}

int UTrapManagerCopmonent::GetLvl(TEnumAsByte<ETrapTypes> Type)
{
	switch (Type)
	{
	case ETrapTypes::Arrows: return arrowLvl;
	case ETrapTypes::Saws: return sawLvl;
	case ETrapTypes::Spikes: return spikesLvl;
	case ETrapTypes::Turrets: return turretLvl;
	default: return 0;
	}
}



