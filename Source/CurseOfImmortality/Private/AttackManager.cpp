// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackManager.h"
#include "GameController.h"

//#define GAME_INSTANCE static_cast<UGameController*>(GetGameInstance())

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
	static_cast<UGameController*>(GetGameInstance())->BindAbilityController(this);

	UpdateAbilityPool();

}

// Called every frame
void AAttackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


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

void AAttackManager::SpawnFromTemplate(ABaseAbility* Template) const
{
	const FVector Location = Template->GetActorLocation();
	const FRotator Rotation = Template->GetActorRotation();
	FActorSpawnParameters Parameters = FActorSpawnParameters();
	Parameters.Template = Template;
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(Template->GetClass(), &Location, &Rotation, Parameters));
	AbilityInstance->SetActorLocation(Template->GetActorLocation());

	//UE_LOG(LogTemp, Error, TEXT("Location of Original %s"), *Template->GetActorLocation().ToString());
	//UE_LOG(LogTemp, Error, TEXT("Location after Spawning %s"), *AbilityInstance->GetActorLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("templated Spawn was triggered"));

	AbilityInstance->ResetLifetime();
	AbilityInstance->AfterInitialization();
}

void AAttackManager::SpawnFromTemplate(ABaseAbility* Template, const FRotator Rotator) const
{
	const FVector Location = Template->GetActorLocation();
	FActorSpawnParameters Parameters = FActorSpawnParameters();
	Parameters.Template = Template;
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(Template->GetClass(), &Location, &Rotator, Parameters));
	AbilityInstance->SetActorLocation(Template->GetActorLocation());
	//UE_LOG(LogTemp, Error, TEXT("Location of Original %s"), *Template->GetActorLocation().ToString());
	//UE_LOG(LogTemp, Error, TEXT("Location after Spawning %s"), *AbilityInstance->GetActorLocation().ToString());
	
	AbilityInstance->ResetLifetime();
	AbilityInstance->AfterInitialization();
	UE_LOG(LogTemp, Warning, TEXT("templated Spawn was triggered"));
}

void AAttackManager::UpdateAbilityPool()
{
	//initial weight per entry = 100
	//some entries start with lower weights, that can be boosted by obtaining other upgrades
	for (const UAbilitySpecification* Ability : PossibleAbilities)
	{
		int Weight = 100;
		bool TypeFound = false; //does the player already have an ability of that type?
		bool AbilityPresent = false; //is the ability already present at it's max level?
		for (const FActiveAbility ActiveAbility : ActiveAbilities)
		{
			if(ActiveAbility.AbilityName == Ability->AbilityName && ActiveAbility.Level == Ability->MaxLevel)
			{
				AbilityPresent = true;
				break;
			}
			if(ActiveAbility.AbilityType == Ability->AbilityType)
			{
				TypeFound = true;
			}
		}

		if(AbilityPresent)
		{
			continue;
		}
		if(TypeFound)
		{
			Weight = 20;
		}
		Pool.Add(FPooledEntry(Ability->AbilityName, false, Weight));
		//pool the ability with the appropriate weight
	}

	for (const UUpgradeSpecification* Upgrade : PossibleUpgrades)
	{
		int Weight = 100;
		bool PrerequisitesMet = false;

		if(Upgrade->Application == EAbilityType::None) //if Type is None, then the Upgrade doesn't require any prerequisites to function
		{
			PrerequisitesMet = true;	
		}
		else
		{
			for (const FActiveAbility ActiveAbility : ActiveAbilities)
			{
				if(ActiveAbility.AbilityType == Upgrade->Application)
				{
					PrerequisitesMet = true;
					break;
				}

			}
		}

		if(!PrerequisitesMet)
		{
			continue;
		}
		
		bool Restricted = false;
		bool UpgradePresent = false;
		for (const FActiveUpgrade ActiveUpgrade : ActiveUpgrades)
		{
			if(ActiveUpgrade.UpgradeName == Upgrade->UpgradeName && ActiveUpgrade.Level == Upgrade->MaxLevel)
			{
				UpgradePresent = true;
				break;
			}
			if(Upgrade->Restrictions.Contains(ActiveUpgrade.UpgradeName))
			{
				Restricted = true;
				break;
			}
		}

		if(Restricted || UpgradePresent)
		{
			continue;
		}

		Pool.Add(FPooledEntry(Upgrade->UpgradeName, true, 100));
	}
	
	UE_LOG(LogTemp, Warning, TEXT("PoolSize %d"), Pool.Num());

}

void AAttackManager::PickThreeFromPool()
{
}

void AAttackManager::OnKeyPressed()
{
	//ABaseAbility* baseAbilityInstance = (ABaseAbility*) GetWorld()->SpawnActor(ABaseAbility::StaticClass());
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(abilityClassType));
	AbilityInstance->InitializeAbility(AbilityMapHandle, this);
	
	for (const auto Upgrade : Upgrades)
	{
		AbilityInstance->AddUpgrade(Upgrade, 1);
	}
	UE_LOG(LogTemp, Warning, TEXT("Spawn was triggered"));
	AbilityInstance->AfterInitialization();

	//const FActiveAbility ActiveAbility = FActiveAbility(AbilityInstance, ActiveUpgrades);
	//ActiveAbilities.Add(AbilityMapHandle, ActiveAbility);
	AbilityMapHandle++;
	//UWorld::SpawnActor(abilityClassType);
}

