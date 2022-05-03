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

	//reduce Cooldowns
	for (const auto Tuple : ActiveAbilities)
	{
		if(Tuple.Value.CurrentCooldown > 0.0f)
		{
			ActiveAbilities[Tuple.Key].CurrentCooldown -= DeltaTime;
			//Tuple.Value -= DeltaTime;
		}
	}

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

void AAttackManager::SortActiveUpgrades(bool Verbose)
{
	if(Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Before Sorting"));

		for (const auto Tuple : ActiveUpgrades)
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Tuple.Value.Specification->DisplayName);
	}

	
	ActiveUpgrades.ValueSort([](const FActiveUpgrade& A, const FActiveUpgrade& B) {
	return A.Specification < B.Specification; // sort strings by length
		});
	
	if(Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("After Sorting"));

		for (const auto Tuple : ActiveUpgrades)
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Tuple.Value.Specification->DisplayName);
	}
	
	
}

bool AAttackManager::CheckCooldown(const EAbilityType Ability)
{
	return ActiveAbilities[Ability].CurrentCooldown <= 0.0f;
}


bool Check(const UAbilitySpecification* Ability, const FActiveAbility& ActiveAbility)
{
	return ActiveAbility.Specification->AbilityName == Ability->AbilityName && ActiveAbility.Level == ActiveAbility.Specification->MaxLevel;
}

void AAttackManager::UpdateAbilityPool()
{
	//initial weight per entry = 100
	//some entries start with lower weights, that can be boosted by obtaining other upgrades

	Pool.Empty();
	
	for (const auto Tuple : PossibleAbilities)
	{
		const auto PossibleAbilityName = Tuple.Key;
		const auto PossibleAbility = Tuple.Value;
		
		if(PossibleAbility == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Ability Specification in PossibleAbilities was NULL"));
			continue;
		}
		int Weight = 100;
		bool TypeFound = false; //does the player already have an ability of that type?
		bool AbilityPresent = false; //is the ability already present at it's max level?

		if(ActiveAbilities.Contains(PossibleAbility->AbilityType))
		{
			TypeFound = true;

			const auto ActiveAbility = ActiveAbilities[PossibleAbility->AbilityType];
			
			if(ActiveAbility.Specification->AbilityName == PossibleAbilityName && ActiveAbility.Level == ActiveAbility.Specification->MaxLevel)
				AbilityPresent = true;

		}
		
		if(AbilityPresent)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Ability %s present at max Level"), *PossibleAbility->DisplayName);
			continue;
		}
		
		if(TypeFound)
		{
			Weight = 20;
		}
		Pool.Add(FPooledEntry(Tuple.Value->AbilityName, false, Weight));
		//pool the ability with the appropriate weight
	}
	

	for (const auto Tuple : PossibleUpgrades)
	{
		const auto PossibleUpgradeName = Tuple.Key;
		const auto PossibleUpgrade = Tuple.Value;
		if(Tuple.Value == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Upgrade Specification in PossibleUpgrades was NULL"));
			continue;
		}

		int Weight = 100;
		bool PrerequisitesMet = false;

		if(PossibleUpgrade->Application == None)
		{
			PrerequisitesMet = true;

		}
		else if(ActiveAbilities.Contains(PossibleUpgrade->Application))
		{
			PrerequisitesMet = true;
		}

		if(!PrerequisitesMet)
			continue;
		
		
		bool Restricted = false;
		bool UpgradePresent = false;
		
		for (const auto BTuple : ActiveUpgrades)
		{
			const auto ActiveUpgradeName = BTuple.Key;
			const auto ActiveUpgrade = BTuple.Value;
			if(ActiveUpgradeName == PossibleUpgradeName && ActiveUpgrade.Level == ActiveUpgrade.Specification->MaxLevel)
			{
				UpgradePresent = true;
				break;
			}
			if(PossibleUpgrade->Restrictions.Contains(ActiveUpgradeName))
			{
				Restricted = true;
				break;
			}
		}

		if(Restricted || UpgradePresent)
			continue;
		

		Pool.Add(FPooledEntry(PossibleUpgradeName, true, Weight));
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("PoolSize %d"), Pool.Num());
}

void AAttackManager::PickThreeFromPool(bool Verbose)
{
	int PoolSize = 0;
	
	for (const auto Entry : Pool)
		PoolSize += Entry.Weight;
	

	SelectedPoolEntries.Empty();
	
	int NumberOfEntries = 3;
	constexpr int MaxIter = 1000;
	int Iter = 0;
	
	if(Pool.Num() < NumberOfEntries)
		NumberOfEntries = Pool.Num();
	
	while(SelectedPoolEntries.Num() < NumberOfEntries && Iter < MaxIter)
	{
		const int Rand = FMath::RandRange(0, PoolSize);
		int Accumulation = 0;
		for (int i = 0; i < Pool.Num(); ++i)
		{
			Accumulation += Pool[i].Weight;
			if(Accumulation > Rand)
			{
				if(!SelectedPoolEntries.Contains(i))
					SelectedPoolEntries.Add(i);
				
				break;
			}
		}
		Iter++;
	}

	if(Verbose)
	{
		for (int i = 0; i < SelectedPoolEntries.Num(); ++i)
		{
			const auto Name = Pool[SelectedPoolEntries[i]].Name;
			if(PossibleAbilities.Contains(Name))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *PossibleAbilities[Name]->DisplayName);
			}
			else if(PossibleUpgrades.Contains(Name))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *PossibleUpgrades[Name]->DisplayName);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Something went wrong! An Upgrade selected, that is not in the Possible Abilites or Possible Upgrades"));
			}
		}
	}
}

void AAttackManager::GetUpgrade(const int Index)
{
	if(Index >= SelectedPoolEntries.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Index %i is out of bounds"), Index);
		return;
	}

	int PoolIndex = SelectedPoolEntries[Index];
	//Get the Upgrade
	if(PoolIndex >= Pool.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Pool was modified in between PickThreeFromPool and GetUpgrade. This is not allowed!"));
		return;
	}

	const FPooledEntry Entry = Pool[PoolIndex];

	//if the Upgrade is an Upgrade-Ability
	if(Entry.Type) 
	{

		if(ActiveUpgrades.Contains(Entry.Name))
		{
			if(ActiveUpgrades[Entry.Name].Level >= ActiveUpgrades[Entry.Name].Specification->MaxLevel)
			{
				UE_LOG(LogTemp, Error, TEXT("Upgrade %s was already max Level, so it can not be leveled up further"), *ActiveUpgrades[Entry.Name].Specification->DisplayName);
				return;
			}

			ActiveUpgrades[Entry.Name].Level++;
		}
		else
		{
			if(PossibleUpgrades.Contains(Entry.Name))
			{
				ActiveUpgrades.Add( Entry.Name,FActiveUpgrade(PossibleUpgrades[Entry.Name], 1));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Upgrade does not exist in Possible Upgrades. This should not happen!"));
				return;
			}
		}
	}
	else //if the Upgrade is a Base-Ability
	{
		bool bFound = false;
		EAbilityType Type = Ranged;
		for(const auto Tuple : ActiveAbilities)
		{
			const auto ActiveAbility = Tuple.Value;
			if(ActiveAbility.Specification->AbilityName == Entry.Name)
			{
				if(ActiveAbility.Level >= ActiveAbility.Specification->MaxLevel)
				{
					UE_LOG(LogTemp, Error, TEXT("Ability %s was already max Level, so it can not be leveled up further"), *ActiveAbilities[Tuple.Value.Specification->AbilityType].Specification->DisplayName);
					return;
				}

				Type = ActiveAbility.Specification->AbilityType;
				bFound = true;
				break;
			}
		}
		if(bFound)
		{
			if(ActiveAbilities.Contains(Type))
			{
				ActiveAbilities[Type].Level++;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Ability Type was ill defined in Ability"));
			}

		}
		else
		{
			if(PossibleAbilities.Contains(Entry.Name))
			{
				ActiveAbilities.Add(PossibleAbilities[Entry.Name]->AbilityType, FActiveAbility(PossibleAbilities[Entry.Name], 1));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Ability does not exist in Possible Abilities. This should not happen!"));
				return;
			}
		}
	}

	SortActiveUpgrades(true);
	UpdateAbilityPool();
}

void AAttackManager::PrintCurrentlyActive()
{
	for (const auto Tuple : ActiveAbilities)
		UE_LOG(LogTemp, Warning, TEXT("BaseAbility: %s Level %i"), *Tuple.Value.Specification->DisplayName, Tuple.Value.Level);

	for (const auto Tuple : ActiveUpgrades)
		UE_LOG(LogTemp, Warning, TEXT("UpgradeAbility: %s Level %i"), *Tuple.Value.Specification->DisplayName, Tuple.Value.Level);
}

void AAttackManager::OnRangedKeyPressed()
{
	if(ActiveAbilities.Contains(Ranged) && CheckCooldown(Ranged))
		SpawnAbility(ActiveAbilities[Ranged]);
}


void AAttackManager::OnSpecialKeyPressed()
{
	if(ActiveAbilities.Contains(Special) && CheckCooldown(Special))
		SpawnAbility(ActiveAbilities[Special]);
}

void AAttackManager::SpawnAbility(FActiveAbility& Ability)
{
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(Ability.Specification->Class));
	AbilityInstance->InitializeAbility(AbilityMapHandle, this, Ability.Level);
	AbilityInstance->OnAbilityCreation();

	//AbilityInstance->AbilityType
	
	for (const auto Tuple : ActiveUpgrades)
	{

		//only upgrades that work with the AbilityType will be applied to the Ability
		if(Tuple.Value.Specification->Application != None)
		{
			if(Tuple.Value.Specification->Application != Ability.Specification->AbilityType)
			{

				continue;
			}
		}	
		AbilityInstance->AddUpgrade(Tuple.Value.Specification->Class, Tuple.Value.Level);
	}
	AbilityInstance->AfterInitialization();

	//const FActiveAbility ActiveAbility = FActiveAbility(AbilityInstance, ActiveUpgrades);
	//ActiveAbilities.Add(AbilityMapHandle, ActiveAbility);
	AbilityMapHandle++;


	//set Cooldown
	if(Ability.Specification->Cooldown.Num() < Ability.Level)
	{
		UE_LOG(LogTemp, Error, TEXT("Ability Cooldown Array had fewer entries than there are Ability-Levels"));
		return;
	}

	Ability.CurrentCooldown = Ability.Specification->Cooldown[Ability.Level-1];
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