// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackManager.h"

#include "AbilitySpecification.h"
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
	SortActiveUpgrades();

}

void AAttackManager::CleanupAbility(int AbilityHandle)
{
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
		InputComponent->BindAction("TestInputRanged", IE_Pressed, this, &AAttackManager::OnRangedKeyPressed);	
		InputComponent->BindAction("testInputSpecial", IE_Pressed, this, &AAttackManager::OnSpecialKeyPressed);	

		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AAttackManager::SortActiveUpgrades()
{
	//Sort: Attribute Setters -> Attribute Setters/Readers -> Attribute Readers
}


bool Check(const UAbilitySpecification* Ability, const FActiveAbility& ActiveAbility)
{
	if(ActiveAbility.Specification->AbilityName == Ability->AbilityName && ActiveAbility.Level == Ability->MaxLevel)
	{
		return true; //ability is present and max Level
	}
	return false;
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

		switch(Ability->AbilityType)
		{
		case Ranged:
			if(ActiveRangedAbility.Specification != nullptr)
			{
				TypeFound = true;
			}
			break;
		case Skill:
			if(ActiveSpecialAbility.Specification != nullptr)
			{
				TypeFound = true;
			}
			break;
		default: ;
		}

		if(Check(Ability, ActiveRangedAbility) || Check(Ability, ActiveSpecialAbility))
		{
			AbilityPresent = true;
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

		switch(Upgrade->Application)
		{
		case None:
			PrerequisitesMet = true;
			break;
		case Ranged:
			if(ActiveRangedAbility.Specification != nullptr)
			{
				PrerequisitesMet = true;
			}
			break;
		case Skill:
			if(ActiveSpecialAbility.Specification != nullptr)
			{
				PrerequisitesMet = true;
			}
			break;
		default: ;
		}

		if(!PrerequisitesMet)
		{
			continue;
		}
		
		bool Restricted = false;
		bool UpgradePresent = false;
		for (const auto [Specification, Level] : ActiveUpgrades)
		{
			if(Specification->UpgradeName == Upgrade->UpgradeName && Level == Upgrade->MaxLevel)
			{
				UpgradePresent = true;
				break;
			}
			if(Upgrade->Restrictions.Contains(Specification->UpgradeName))
			{
				Restricted = true;
				break;
			}
		}

		if(Restricted || UpgradePresent)
		{
			continue;
		}

		Pool.Add(FPooledEntry(Upgrade->UpgradeName, true, Weight));
	}
	
	UE_LOG(LogTemp, Warning, TEXT("PoolSize %d"), Pool.Num());

}

void AAttackManager::PickThreeFromPool()
{
}

void AAttackManager::GetUpgrade()
{
	//Get the Upgrade
	SortActiveUpgrades();
}

void AAttackManager::OnRangedKeyPressed()
{
	SpawnAbility(ActiveRangedAbility);
}


void AAttackManager::OnSpecialKeyPressed()
{
	SpawnAbility(ActiveSpecialAbility);
}

void AAttackManager::SpawnAbility(const FActiveAbility& Ability)
{
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(Ability.Specification->Class));
	AbilityInstance->InitializeAbility(AbilityMapHandle, this, Ability.Level);
	AbilityInstance->OnAbilityCreation();

	//AbilityInstance->AbilityType
	
	for (const auto [Specification, Level] : ActiveUpgrades)
	{

		//only upgrades that work with the AbilityType will be applied to the Ability
		if(Specification->Application != None)
		{
			if(Specification->Application != Ability.Specification->AbilityType)
			{

				continue;
			}
		}	
		AbilityInstance->AddUpgrade(Specification->Class, Level);
	}
	AbilityInstance->AfterInitialization();

	//const FActiveAbility ActiveAbility = FActiveAbility(AbilityInstance, ActiveUpgrades);
	//ActiveAbilities.Add(AbilityMapHandle, ActiveAbility);
	AbilityMapHandle++;
}

void AAttackManager::SpawnFromTemplate(ABaseAbility* Template) const
{
	SpawnFromTemplate(Template, Template->GetActorRotation());
}

void AAttackManager::SpawnFromTemplate(ABaseAbility* Template, const FRotator Rotator) const
{
	const FVector Location = FVector::Zero();
	FActorSpawnParameters Parameters = FActorSpawnParameters();
	Parameters.Template = Template;
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(Template->GetClass(), &Location, &Rotator, Parameters));
	AbilityInstance->SetActorLocation(Template->GetActorLocation());
	AbilityInstance->OnAbilityCreation();
	AbilityInstance->ResetLifetime();
	AbilityInstance->AfterInitialization();
}

