// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUpgrade.h"

// Sets default values
ABaseUpgrade::ABaseUpgrade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseUpgrade::InitializeUpgrade(ABaseAbility* _AbilityInstance)
{
	
	if(_AbilityInstance)
	{
		_AbilityInstance->OnAbilityStart.AddUObject(this, &ABaseUpgrade::OnAbilityStart);
		_AbilityInstance->OnAbilityEnd.AddUObject(this, &ABaseUpgrade::OnAbilityEnd);
		AbilityInstance = _AbilityInstance;
		//auto s = abilityInstance->OnAbilityStartDelegate.ToString<>();
		//UE_LOG(LogTemp, Warning, TEXT("On Abilitystart was called in Base Upgrade"));
	}
	
}

// Called when the game starts or when spawned
void ABaseUpgrade::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseUpgrade::OnAbilityStart(int AbilityHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("On Abilitystart was called in Base Upgrade"));
}

void ABaseUpgrade::OnAbilityEnd(int AbilityHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("On Abilityend was called in Base Upgrade"));
}


// Called every frame
void ABaseUpgrade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

