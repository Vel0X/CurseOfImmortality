// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUpgrade.h"

// Sets default values
ABaseUpgrade::ABaseUpgrade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseUpgrade::InitializeUpgrade(ABaseAbility* abilityInstance)
{
	abilityInstance->OnAbilityStartDelegate.BindUFunction(this, "OnAbilityStart");
}

// Called when the game starts or when spawned
void ABaseUpgrade::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseUpgrade::OnAbilityStart()
{
	UE_LOG(LogTemp, Warning, TEXT("On Abilitystart was called in Base Upgrade"));
}


// Called every frame
void ABaseUpgrade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

