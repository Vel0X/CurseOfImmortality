// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/Traps/TrapComponent.h"
#include "CurseOfImmortality/Traps/TrapManagerCopmonent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

// Sets default values for this component's properties
UTrapComponent::UTrapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTrapComponent::BeginPlay()
{
	Super::BeginPlay();

	TrapIsActive = false;
	if(FPersistentWorldManager::TrapManager != nullptr)
	{
		FPersistentWorldManager::TrapManager -> UpgradeTraptype.AddDynamic(this, &UTrapComponent::CheckActivation);
		FPersistentWorldManager::TrapManager -> DeactivateTrapsOfType.AddDynamic(this, &UTrapComponent::CheckDeactivation);
	}
}


// Called every frame
void UTrapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/*if(!TimerDone)
	{
		if(Timer >= 0)
		{
			Timer -= DeltaTime;
		}else
		{
			if(FPersistentWorldManager::TrapManager != nullptr)
			{
				FPersistentWorldManager::TrapManager -> UpgradeTraptype.AddDynamic(this, &UTrapComponent::CheckActivation);
				FPersistentWorldManager::TrapManager -> DeactivateTrapsOfType.AddDynamic(this, &UTrapComponent::CheckDeactivation);
				TimerDone = true;
			} else
			{
				UE_LOG(LogTemp, Display, TEXT("Failed Trap"));
			}
		}	
	}*/
}

void UTrapComponent::CheckActivation(TEnumAsByte<ETrapTypes> OtherTrapType, int prio)
{
	//UE_LOG(LogTemp, Display, TEXT("Check Trap"));
	if(OtherTrapType == TrapType && prio >= Prio || OtherTrapType == ETrapTypes::All )
	{
		//UE_LOG(LogTemp, Display, TEXT("%s"), *GetOwner()->GetName());
		TrapIsActive = true;
	}
}

void UTrapComponent::CheckDeactivation(TEnumAsByte<ETrapTypes> OtherTrapType = ETrapTypes::All, int prio = 0)
{
	if(OtherTrapType == TrapType && prio <= Prio || OtherTrapType == ETrapTypes::All)
	{
		TrapIsActive = false;
	}
}


