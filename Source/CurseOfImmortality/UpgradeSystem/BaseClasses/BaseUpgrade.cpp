// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseUpgrade.h"
#include "BaseAbility.h"

// Sets default values for this component's properties
UBaseUpgrade::UBaseUpgrade()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UBaseUpgrade::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	if(_AbilityInstance)
	{
		//_AbilityInstance->OnAbilityStart.AddUObject(this, &UBaseUpgrade::OnAbilityStart);
		//_AbilityInstance->OnAbilityEnd.AddUObject(this, &UBaseUpgrade::OnAbilityEnd);
		AbilityInstance = _AbilityInstance; //grab a reference to the Ability (might not be needed since component should easily access it anyway)
		//auto s = abilityInstance->OnAbilityStartDelegate.ToString<>();
		//UE_LOG(LogTemp, Warning, TEXT("On Abilitystart was called in Base Upgrade"));
	}
}



// Called when the game starts
void UBaseUpgrade::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UBaseUpgrade::OnAbilityStart(int AbilityHandle)
{
	//UE_LOG(LogTemp, Warning, TEXT("On Abilitystart was called in Base Upgrade"));
}

void UBaseUpgrade::OnAbilityEnd(int AbilityHandle)
{
	//UE_LOG(LogTemp, Warning, TEXT("On Abilityend was called in Base Upgrade"));
}

void UBaseUpgrade::OnEnemyHit(ABaseCharacter* Enemy)
{
	
}

void UBaseUpgrade::OnAbilityHit(ARangedAbility* Ability)
{
	
}

