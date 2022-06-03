// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackManager.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "DataAssets/AbilitySpecification.h"

//#define GAME_INSTANCE static_cast<UGameController*>(GetGameInstance())

// Sets default values
UAttackManager::UAttackManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttackManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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


// Called when the game starts or when spawned
void UAttackManager::BeginPlay()
{
	Super::BeginPlay();
	FPersistentWorldManager::AttackManager = this;
	UpdateAbilityPool();
	SortActiveUpgrades(true);

}

void UAttackManager::SortActiveUpgrades(bool Verbose)
{
	if(Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Before Sorting"));

		for (const auto Tuple : ActiveUpgrades)
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Tuple.Value.Specification->DisplayName);
	}

	
	ActiveUpgrades.ValueSort([](const FActiveUpgrade& A, const FActiveUpgrade& B) {
	return A.Specification->UpgradeOrder < B.Specification->UpgradeOrder; // sort strings by length
		});
	
	if(Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("After Sorting"));

		for (const auto Tuple : ActiveUpgrades)
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Tuple.Value.Specification->DisplayName);
	}
	
	
}

bool UAttackManager::CheckCooldown(const EAbilityType Ability)
{
	//const auto CD= ActiveAbilities[Ability].CurrentCooldown;
	//UE_LOG(LogTemp, Warning, TEXT("cd %f"), CD);
	return ActiveAbilities[Ability].CurrentCooldown <= 0.0f;
}


bool Check(const UAbilitySpecification* Ability, const FActiveAbility& ActiveAbility)
{
	return ActiveAbility.Specification->AbilityName == Ability->AbilityName && ActiveAbility.Level == ActiveAbility.Specification->MaxLevel;
}

void UAttackManager::UpdateAbilityPool()
{
	//initial weight per entry = 100
	//some entries start with lower weights, that can be boosted by obtaining other upgrades

	Pool.Empty();

	
	for (const auto Tuple : PossibleUpgrades->PossibleBaseAbilities)
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
		Pool.Add(FPooledEntry(PossibleAbilityName, false, Weight));
		//pool the ability with the appropriate weight
	}
	

	for (const auto Tuple : PossibleUpgrades->PossibleUpgradeAbilities)
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

void UAttackManager::PickThreeFromPool(bool Verbose)
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
			if(PossibleUpgrades->PossibleBaseAbilities.Contains(Name))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *PossibleUpgrades->PossibleBaseAbilities[Name]->DisplayName);
			}
			else if(PossibleUpgrades->PossibleUpgradeAbilities.Contains(Name))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *PossibleUpgrades->PossibleUpgradeAbilities[Name]->DisplayName);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Something went wrong! An Upgrade selected, that is not in the Possible Abilites or Possible Upgrades"));
			}
		}
	}
	
}

TArray<FDisplayInformation> UAttackManager::GetDisplayInformation()
{
	TArray<FDisplayInformation> DisplayInformation;
	//Pool[SelectedPoolEntries[0]].Name;
	for (int i = 0; i < SelectedPoolEntries.Num(); ++i)
	{
		auto Entry = Pool[SelectedPoolEntries[i]];
		if(Entry.Type)
		{
			const auto Spec = PossibleUpgrades->PossibleUpgradeAbilities[Entry.Name];
			if(Spec == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Something went wrong! Upgrade Specification was NULL"));
				continue;
			}

			FText Application = FText();
			//Application
			switch(Spec->Application)
			{
			case None:
				Application = Application.FromString("Upgrade");
				break;
			case Melee:
				Application = Application.FromString("Melee Only Upgrade");
				break;
			case Ranged:
				Application = Application.FromString("Ranged Only Upgrade");
				break;
			case Special:
				Application = Application.FromString("Special Only Upgrade");
				break;
			default: ;
			}
			
			DisplayInformation.Add(FDisplayInformation(Spec->DisplayName, Application, Spec->Description, Spec->Image));
		}
		else
		{
			const auto Spec = PossibleUpgrades->PossibleBaseAbilities[Entry.Name];
			if(Spec == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Something went wrong! Ability Specification was NULL"));
				continue;
			}

			FText Application = FText();
			//Application
			switch(Spec->AbilityType)
			{
			case Melee:
				Application = Application.FromString("Melee Base Ability");
				break;
			case Ranged:
				Application = Application.FromString("Ranged Base Ability");
				break;
			case Special:
				Application = Application.FromString("Special Base Ability");
				break;
			default: ;
			}
			
			DisplayInformation.Add(FDisplayInformation(Spec->DisplayName, Application, Spec->Description, Spec->Image));
		}
	}
	return DisplayInformation;
}

void UAttackManager::GetUpgrade(const int Index)
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
			if(PossibleUpgrades->PossibleUpgradeAbilities.Contains(Entry.Name))
			{
				ActiveUpgrades.Add( Entry.Name,FActiveUpgrade(PossibleUpgrades->PossibleUpgradeAbilities[Entry.Name], 1));
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
			if(PossibleUpgrades->PossibleBaseAbilities.Contains(Entry.Name))
			{
				ActiveAbilities.Add(PossibleUpgrades->PossibleBaseAbilities[Entry.Name]->AbilityType, FActiveAbility(PossibleUpgrades->PossibleBaseAbilities[Entry.Name], 1));
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

void UAttackManager::PrintCurrentlyActive()
{
	for (const auto Tuple : ActiveAbilities)
		UE_LOG(LogTemp, Warning, TEXT("BaseAbility: %s Level %i"), *Tuple.Value.Specification->DisplayName, Tuple.Value.Level);

	for (const auto Tuple : ActiveUpgrades)
		UE_LOG(LogTemp, Warning, TEXT("UpgradeAbility: %s Level %i"), *Tuple.Value.Specification->DisplayName, Tuple.Value.Level);
}

void UAttackManager::OnKeyPressed(EAbilityType Type)
{
	if(ActiveAbilities.Contains(Type) && CheckCooldown(Type))
		SpawnAbility(ActiveAbilities[Type]);
}



void UAttackManager::SpawnAbility(FActiveAbility& Ability)
{
	const ABaseCharacter* Owner = Cast<ABaseCharacter>(GetOwner());

	const FRotator Rotation = Owner->GetActorRotation();
	const FVector Location = Owner->GetActorLocation();

	SpawnAbility(Ability, Location, Rotation);
}

void UAttackManager::SpawnAbility(FActiveAbility& Ability, FVector Position, FRotator Rotation)
{
	ABaseCharacter* Owner = Cast<ABaseCharacter>(GetOwner());
	
	//FPersistentWorldManager::ObjectFactory->SpawnAbility(Ability.Specification->AbilityName, Location, Rotation, Owner);

	ABaseAbility* AbilityInstance = Cast<ABaseAbility>(GetWorld()->SpawnActor(Ability.Specification->Class, &Position, &Rotation));

	if(AbilityInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Abiltiy could not be spawned!"));
		return;
	}
	AbilityInstance->InitializeAbility(Owner, Ability.Level);
	AbilityInstance->OnAbilityCreation();
	//AbilityInstance->AbilityType

	for (const auto Tuple : ActiveUpgrades)
	{

		//only upgrades that work with the AbilityType will be applied to the Ability
		if(Tuple.Value.Specification->Application != None && Tuple.Value.Specification->Application != Ability.Specification->AbilityType)
				continue;
		
		//UE_LOG(LogTemp, Error, TEXT("Added %s"), *Tuple.Value.Specification->DisplayName);
		AbilityInstance->AddUpgrade(Tuple.Value.Specification->Class, Tuple.Value.Level);
	}
	AbilityInstance->AfterInitialization();

	//const FActiveAbility ActiveAbility = FActiveAbility(AbilityInstance, ActiveUpgrades);
	//ActiveAbilities.Add(AbilityMapHandle, ActiveAbility);


	//set Cooldown
	if(Ability.Specification->Cooldown.Num() < Ability.Level)
	{
		UE_LOG(LogTemp, Error, TEXT("Ability Cooldown Array had fewer entries than there are Ability-Levels"));
		return;
	}

	Ability.CurrentCooldown = Ability.Specification->Cooldown[Ability.Level-1];
}

void UAttackManager::SpawnAbility(EAbilityType Ability)
{
	if(ActiveAbilities.Contains(Ability) && CheckCooldown(Ability))
		SpawnAbility(ActiveAbilities[Ability]);
}

void UAttackManager::SpawnAbilityRotationSpecified(EAbilityType Ability, FVector Position, FRotator Rotation)
{
	if(ActiveAbilities.Contains(Ability) && CheckCooldown(Ability))
		SpawnAbility(ActiveAbilities[Ability], Position, Rotation);
}


void UAttackManager::SpawnFromTemplate(ABaseAbility* Template) const
{
	SpawnFromTemplate(Template, Template->GetActorLocation(), Template->GetActorRotation());
}

void UAttackManager::SpawnFromTemplate(ABaseAbility* Template,const FVector Position, const FRotator Rotator) const
{
	//const FVector Location = FVector::Zero();
	FActorSpawnParameters Parameters = FActorSpawnParameters();
	Parameters.Template = Template;
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(Template->GetClass(), &Position, &Rotator, Parameters));
	AbilityInstance->SetActorLocation(Position);
	AbilityInstance->SetActorRotation(Rotator);
	AbilityInstance->OnAbilityCreation();
	AbilityInstance->ResetLifetime();
	AbilityInstance->AfterInitialization();
}