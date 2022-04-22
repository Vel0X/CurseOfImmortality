// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"
#include "BaseUpgrade.h"

// Sets default values
ABaseAbility::ABaseAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("????"));
	//UE_LOG(LogTemp, Warning, TEXT("%s"), &OnAbilityStartDelegate);
}

// Called when the game starts or when spawned
void ABaseAbility::BeginPlay()
{
	Super::BeginPlay();
	RemainingAbilityLifetime = AbilityLifetime;
	OnActorBeginOverlap.AddDynamic( this, &ABaseAbility::OnEnemyHit);

	//UE_LOG(LogTemp, Warning, TEXT("AbilityInstance was spawned (Base)"));
	//OnActorBeginOverlap.AddDynamic(this, &ABaseAbility::AtOverlap);

}

void ABaseAbility::OnEnemyHit(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!CanInteract)
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Enemy was hit"));
	for (const auto Upgrade : UpgradeStack)
	{
		if(Upgrade == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL in list"));
		}
		else
		{
			Upgrade->OnEnemyHit();
		}
	}
	if(DestroyOnEnemyHit)
	{
		UE_LOG(LogTemp, Error, TEXT("Ability was destroyed on Enemyhit"));
		DestroyAbility();
	}
}

// Called every frame
void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RemainingAbilityLifetime -= DeltaTime;
	if(RemainingAbilityLifetime <= 0.0f)
	{
		DestroyAbility();
	}
	CanInteract = true;
}

void ABaseAbility::InitializeAbility(int _AbilityHandle)
{
	AbilityHandle = _AbilityHandle;
}

void ABaseAbility::AfterInitialization() const
{
	for (const auto Upgrade : UpgradeStack)
	{
		if(Upgrade == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL in list"));
		}
		else
		{
			Upgrade->OnAbilityStart(AbilityHandle);
		}
			
	}
		//OnAbilityStart.Broadcast(AbilityHandle);
}

void ABaseAbility::DestroyAbility()
{
	//OnAbilityEnd.Broadcast(AbilityHandle);
	for (const auto Upgrade : UpgradeStack)
	{
		if(Upgrade == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL in list"));
		}
		else
		{
			Upgrade->OnAbilityEnd(AbilityHandle);
		}
	}
	Destroy();
}

void ABaseAbility::AddUpgrade(const TSubclassOf<UBaseUpgrade>& Class, int UpgradeLevel)
{
	/*
	auto Upgrade = AddComponentByClass(Class, false, GetTransform(), false);

	if(Upgrade == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL after cast"));
	}
	*/
	
	UBaseUpgrade* Upgrade = static_cast<UBaseUpgrade*>(AddComponentByClass(Class, false, FTransform::Identity, false));
	if(Upgrade == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL after cast"));
	}
	else
	{
		Upgrade->InitializeUpgrade(this, UpgradeLevel);
		UpgradeStack.Add(Upgrade);
	}
	
}

void ABaseAbility::ResetLifetime()
{
	RemainingAbilityLifetime = AbilityLifetime;
}

