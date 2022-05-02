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

void AAttackManager::SortActiveUpgrades()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Before Sorting"));

	for (int i = 0; i < ActiveUpgrades.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActiveUpgrades[i].Specification->DisplayName);
	}
	
	
	
	ActiveUpgrades.Sort();

	
	UE_LOG(LogTemp, Warning, TEXT("After Sorting"));
	
	for (int i = 0; i < ActiveUpgrades.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActiveUpgrades[i].Specification->DisplayName);
	}
	
}

bool AAttackManager::CheckCooldown(const EAbilityType Ability)
{
	
	return ActiveAbilities[Ability].CurrentCooldown <= 0.0f;

}


bool Check(const UAbilitySpecification* Ability, const FActiveAbility& ActiveAbility)
{
	return ActiveAbility.Specification->AbilityName == Ability->AbilityName && ActiveAbility.Level == Ability->MaxLevel;
}

void AAttackManager::UpdateAbilityPool()
{
	//initial weight per entry = 100
	//some entries start with lower weights, that can be boosted by obtaining other upgrades

	for (const auto Tuple : PossibleAbilities)
	{
		int Weight = 100;
		bool TypeFound = false; //does the player already have an ability of that type?
		bool AbilityPresent = false; //is the ability already present at it's max level?

		if(ActiveAbilities.Contains(Tuple.Value->AbilityType))
		{
			TypeFound = true;
			if(Check(Tuple.Value, ActiveAbilities[Tuple.Value->AbilityType]))
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
		Pool.Add(FPooledEntry(Tuple.Value->AbilityName, false, Weight));
		//pool the ability with the appropriate weight
	}
	

	for (const auto Tuple : PossibleUpgrades)
	{
		int Weight = 100;
		bool PrerequisitesMet = false;

		if(Tuple.Value->Application == None)
		{
			PrerequisitesMet = true;

		}
		else if(ActiveAbilities.Contains(Tuple.Value->Application))
		{
			PrerequisitesMet = true;
		}

		if(!PrerequisitesMet)
		{
			continue;
		}
		
		bool Restricted = false;
		bool UpgradePresent = false;
		for (const auto [Specification, Level] : ActiveUpgrades)
		{
			if(Specification->UpgradeName == Tuple.Value->UpgradeName && Level == Tuple.Value->MaxLevel)
			{
				UpgradePresent = true;
				break;
			}
			if(Tuple.Value->Restrictions.Contains(Specification->UpgradeName))
			{
				Restricted = true;
				break;
			}
		}

		if(Restricted || UpgradePresent)
		{
			continue;
		}

		Pool.Add(FPooledEntry(Tuple.Value->UpgradeName, true, Weight));
	}
	
	UE_LOG(LogTemp, Warning, TEXT("PoolSize %d"), Pool.Num());

}

void AAttackManager::PickThreeFromPool()
{
	int PoolSize = 0;
	for (const auto Entry : Pool)
	{
		PoolSize += Entry.Weight;
	}

	SelectedPoolEntries.Empty();
	
	int NumberOfEntries = 3;
	constexpr int MaxIter = 1000;
	int Iter = 0;
	if(Pool.Num() < NumberOfEntries)
	{
		NumberOfEntries = Pool.Num();
	}
	
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
				{
					SelectedPoolEntries.Add(i);
				}
				break;
			}
		}
		Iter++;
	}

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
		bool bFound = false;
		//if the Upgrade is already in the Active Upgrades, increase its Level
		for (int i = 0; i < ActiveUpgrades.Num(); ++i)
		{
			if (Entry.Name == ActiveUpgrades[i].Specification->UpgradeName)
			{
				if(ActiveUpgrades[i].Level >= ActiveUpgrades[i].Specification->MaxLevel)
				{
					//UE_LOG(LogTemp, Error, TEXT("Upgrade was already max Level, so it can not be leveled up further %s"), ActiveUpgrades[i].Specification->DisplayName);
					return;
				}
				
				ActiveUpgrades[i].Level++;
				bFound = true;
				break;
			}
		}

		//if the Upgrade us not in Active Upgrades, get it from the Possible Upgrades
		if(!bFound)
		{
			if(PossibleUpgrades.Contains(Entry.Name))
			{
				ActiveUpgrades.Add(FActiveUpgrade(PossibleUpgrades[Entry.Name], 1));
			}
		}
	}

	/*
	else
	{
		if(ActiveRangedAbility.Specification->AbilityName == Entry.Name)
		{
			if(ActiveRangedAbility.Level >= ActiveRangedAbility.Specification->MaxLevel)
			{
				//UE_LOG(LogTemp, Error, TEXT("Ability was already max Level, so it can not be leveled up further %s"), ActiveRangedAbility.Specification->DisplayName);
				return;
			}
				
			ActiveRangedAbility.Level++;
		}
		else if(ActiveSpecialAbility.Specification->AbilityName == Entry.Name)
		{
			if(ActiveSpecialAbility.Level >= ActiveSpecialAbility.Specification->MaxLevel)
			{
				//UE_LOG(LogTemp, Error, TEXT("Ability was already max Level, so it can not be leveled up further %s"), ActiveSpecialAbility.Specification->DisplayName);
				return;
			}
				
			ActiveSpecialAbility.Level++;
		}
		else
		{
			for (int i = 0; i < PossibleAbilities.Num(); ++i)
			{
				if(Entry.Name == PossibleAbilities[i]->AbilityName)
				{
					if(PossibleAbilities[i]->AbilityType == Ranged)
					{
						ActiveRangedAbility = FActiveAbility(PossibleAbilities[i], 1);
					}
					else
					{
						ActiveSpecialAbility = FActiveAbility(PossibleAbilities[i], 1);
					}
					break;
				}
			}
		}
	}
	*/
	SortActiveUpgrades();
}

void AAttackManager::PrintCurrentlyActive()
{
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