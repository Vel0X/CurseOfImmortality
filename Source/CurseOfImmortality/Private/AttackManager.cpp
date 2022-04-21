// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"

#include "AttackManager.h"

// Sets default values
AAttackManager::AAttackManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAttackManager::BeginPlay()
{
	Super::BeginPlay();
	BindToInput();
	//((UGameController*)GetGameInstance())->BindAbilityController();

}

void AAttackManager::CleanupAbility(int AbilityHandle)
{
	ActiveAbilities.Remove(AbilityHandle);
	UE_LOG(LogTemp, Warning, TEXT("Removed AbilityInstance from List. Remaining are %d abilities"), ActiveAbilities.Num());
	//UE_LOG(LogTemp, Warning, FString::FromInt(ActiveAbilities.Num());

}

// Called every frame
void AAttackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//printf("?????");
	//UE_LOG(LogTemp, Warning, TEXT("Test"));


}

void AAttackManager::BindToInput() 
{
	// Initialize our component
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		// Bind inputs here
		// InputComponent->BindAction("Jump", IE_Pressed, this, &AUnrealisticPawn::Jump);
		// etc...
		InputComponent->BindAction("TestInputZ", IE_Pressed, this, &AAttackManager::OnKeyPressed);	

		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());

	}
}

void AAttackManager::SpawnFromTemplate(FActiveAbility Template)
{
	TArray<ABaseUpgrade*> ActiveUpgrades;
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(Template.AbilityInstance->GetClass()));
	AbilityInstance->InitializeAbility(AbilityMapHandle);

	for (const auto Upgrade : Template.ActiveUpgrades)
	{
		ABaseUpgrade* UpgradeInstance = static_cast<ABaseUpgrade*>(GetWorld()->SpawnActor(Upgrade->GetClass()));
		UpgradeInstance->InitializeUpgrade(AbilityInstance);
		ActiveUpgrades.Add(UpgradeInstance);
	}

	AbilityInstance->OnAbilityEnd.AddUObject(this, &AAttackManager::CleanupAbility);
	
	AbilityInstance->AfterInitialization();

	const FActiveAbility ActiveAbility = FActiveAbility(AbilityInstance, ActiveUpgrades);
	ActiveAbilities.Add(AbilityMapHandle, ActiveAbility);
	AbilityMapHandle++;
}


void AAttackManager::OnKeyPressed()
{
	//ABaseAbility* baseAbilityInstance = (ABaseAbility*) GetWorld()->SpawnActor(ABaseAbility::StaticClass());
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(abilityClassType));
	AbilityInstance->InitializeAbility(AbilityMapHandle);
	TArray<ABaseUpgrade*> ActiveUpgrades;
	
	for (const auto Upgrade : Upgrades)
	{

		ABaseUpgrade* UpgradeInstance = static_cast<ABaseUpgrade*>(GetWorld()->SpawnActor(Upgrade));
		if(UpgradeInstance == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Upgrade couldnt be instantiated"));
		}
		else
		{
			UpgradeInstance->InitializeUpgrade(AbilityInstance);
			ActiveUpgrades.Add(UpgradeInstance);
		}


		/*
		if(AbilityInstance->AbilityType == Upgrade->RestrictedTo)
		{
			
			Upgrade->InitializeUpgrade(AbilityInstance);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Upgrade couldn't be applied to ability due to differing types"));
		}
		*/
	}

	AbilityInstance->OnAbilityEnd.AddUObject(this, &AAttackManager::CleanupAbility);
	
	AbilityInstance->AfterInitialization();

	const FActiveAbility ActiveAbility = FActiveAbility(AbilityInstance, ActiveUpgrades);
	ActiveAbilities.Add(AbilityMapHandle, ActiveAbility);
	AbilityMapHandle++;
	//UWorld::SpawnActor(abilityClassType);
}

