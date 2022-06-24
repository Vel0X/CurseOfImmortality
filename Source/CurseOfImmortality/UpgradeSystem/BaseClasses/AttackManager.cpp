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
	SortActiveUpgrades();

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
	if(!ActiveAbilities.Contains(Ability))
		return false;

	if(!ActiveAbilities[Ability].Specification)
		return false;
	
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
		bool AbilityMaxed = false; //is the ability already present at it's max level?
		int AbilityLevel = 0;
		if(ActiveAbilities.Contains(PossibleAbility->AbilityType) && ActiveAbilities[PossibleAbility->AbilityType].Specification)
		{
			TypeFound = true;

			const auto ActiveAbility = ActiveAbilities[PossibleAbility->AbilityType];
			
			if(ActiveAbility.Specification->AbilityName == PossibleAbilityName)
			{
				AbilityLevel = ActiveAbility.Level;
				if(ActiveAbility.Level == ActiveAbility.Specification->MaxLevel)
				{
					AbilityMaxed = true;
				}
			} 

		}
		
		if(AbilityMaxed)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Ability %s present at max Level"), *PossibleAbility->DisplayName);
			continue;
		}
		
		if(TypeFound)
		{
			Weight = 20;
		}
		Pool.Add(FPooledEntry(PossibleAbilityName, AbilityLevel, false, Weight));
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
		bool UpgradeMaxed = false;
		int UpgradeLevel = 0;
		
		for (const auto BTuple : ActiveUpgrades)
		{
			const auto ActiveUpgradeName = BTuple.Key;
			const auto ActiveUpgrade = BTuple.Value;
			if(ActiveUpgradeName == PossibleUpgradeName)
			{
				UpgradeLevel = ActiveUpgrade.Level;
				if(ActiveUpgrade.Level == ActiveUpgrade.Specification->MaxLevel)
				{
					UpgradeMaxed = true;
					break;
				}

			}
			if(PossibleUpgrade->Restrictions.Contains(ActiveUpgradeName))
			{
				Restricted = true;
				break;
			}
		}

		if(Restricted || UpgradeMaxed)
			continue;
		

		Pool.Add(FPooledEntry(PossibleUpgradeName, UpgradeLevel, true, Weight));
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

TArray<UDisplayInformation*> UAttackManager::GetUpgradeDisplayInformation()
{
	TArray<UDisplayInformation*> DisplayInformation;
	//Pool[SelectedPoolEntries[0]].Name;
	for (int i = 0; i < SelectedPoolEntries.Num(); ++i)
	{
		const auto Entry = Pool[SelectedPoolEntries[i]];
		if(Entry.Type)
		{
			const auto Spec = PossibleUpgrades->PossibleUpgradeAbilities[Entry.Name];
			if(Spec == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Something went wrong! Upgrade Specification was NULL"));
				continue;
			}

			const FText Application = GetUpgradeApplication(Spec->Application);
			AddDisplayInformation(DisplayInformation, Spec->DisplayName, Application, Spec->Description, Spec->Image, Entry.CurrentLevel);
		}
		else
		{
			const auto Spec = PossibleUpgrades->PossibleBaseAbilities[Entry.Name];
			if(Spec == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Something went wrong! Ability Specification was NULL"));
				continue;
			}

			const FText Application = GetAbilityApplication(Spec->AbilityType);
			AddDisplayInformation(DisplayInformation, Spec->DisplayName, Application, Spec->Description, Spec->Image, Entry.CurrentLevel);
		}
	}
	return DisplayInformation;
}

void UAttackManager::AddDisplayInformation(TArray<UDisplayInformation*>& List, FString Name, const FText Application,
                                           const FText Description, UTexture2D* Texture, const int Level) const
{
	const auto DisplayInfo = NewObject<UDisplayInformation>();
	DisplayInfo->DisplayName = Name;
	DisplayInfo->Application = Application;
	DisplayInfo->Description = Description;
	DisplayInfo->Image = Texture;
	DisplayInfo->Level = Level;
	List.Add(DisplayInfo);
}

void UAttackManager::GetActivesDisplayInformation(
	TMap<TEnumAsByte<EAbilityType>, UDisplayInformation*>& ActiveBaseAbilitiesDisplayInfo,
	TArray<UDisplayInformation*>& ActiveUpgradeDisplayInfo)
{
	for (const auto Tuple : ActiveAbilities)
	{
		auto Type = Tuple.Key;
		const auto ActiveAbility = Tuple.Value;
		const auto Spec = ActiveAbility.Specification;
		if(Spec == nullptr)
		{
			ActiveBaseAbilitiesDisplayInfo.Add(Type, nullptr);
			continue;
		}
		const FText Application = GetUpgradeApplication(Spec->AbilityType);

		auto DisplayInfo = NewObject<UDisplayInformation>();
		DisplayInfo->DisplayName = Spec->DisplayName;
		DisplayInfo->Application = Application;
		DisplayInfo->Description = Spec->Description;
		DisplayInfo->Image = Spec->Image;
		DisplayInfo->Level = ActiveAbility.Level;
		ActiveBaseAbilitiesDisplayInfo.Add(Type, DisplayInfo);
	}

	for (const auto Tuple : ActiveUpgrades)
	{
		const auto ActiveUpgrade = Tuple.Value;
		const auto Spec = ActiveUpgrade.Specification;
		const FText Application = GetUpgradeApplication(Spec->Application);
		AddDisplayInformation(ActiveUpgradeDisplayInfo, Spec->DisplayName, Application, Spec->Description, Spec->Image, ActiveUpgrade.Level);
	}
}

FText UAttackManager::GetAbilityApplication(const EAbilityType Type)
{
	FText Application = FText();
	//Application
	switch(Type)
	{
	case Melee:
		return Application.FromString("Melee Base Ability");
	case Ranged:
		return Application.FromString("Ranged Base Ability");
	case Special:
		return Application.FromString("Special Base Ability");
	default: return Application;
	}
}

FText UAttackManager::GetUpgradeApplication(const EAbilityType Type)
{
	FText Application = FText();
	//Application
	switch(Type)
	{
	case None:
		return Application.FromString("Upgrade");
	case Melee:
		return Application.FromString("Melee Only Upgrade");
	case Ranged:
		return Application.FromString("Ranged Only Upgrade");
	case Special:
		return Application.FromString("Special Only Upgrade");
	default: return Application;
	}
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

			if(!ActiveAbility.Specification)
				continue;

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
				const auto Key = PossibleUpgrades->PossibleBaseAbilities[Entry.Name]->AbilityType;
				const auto Ability = FActiveAbility(PossibleUpgrades->PossibleBaseAbilities[Entry.Name], 1);
				if(ActiveAbilities.Contains(Key))
					ActiveAbilities[Key] = Ability;
				else
					ActiveAbilities.Add(Key, Ability);
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

void UAttackManager::OnKeyPressed(EAbilityType Type, FVector SpawnLocation)
{
	if(ActiveAbilities.Contains(Type) && CheckCooldown(Type))
		SpawnAbility(ActiveAbilities[Type], SpawnLocation);
}



void UAttackManager::SpawnAbility(FActiveAbility& Ability, FVector SpawnLocation)
{
	const ABaseCharacter* Owner = Cast<ABaseCharacter>(GetOwner());

	const FRotator Rotation = Owner->GetActorRotation();
	const FVector Location = SpawnLocation;

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
	AbilityInstance->InitializeAbility(Owner, Ability.Level, Ability.Specification);
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
		SpawnAbility(ActiveAbilities[Ability], GetOwner()->GetActorLocation());
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
	ABaseAbility* AbilityInstance = Cast<ABaseAbility>(GetWorld()->SpawnActor(Template->GetClass(), &Position, &Rotator, Parameters));
	AbilityInstance->SetActorLocation(Position);
	AbilityInstance->SetActorRotation(Rotator);
	AbilityInstance->OnAbilityCreation();
	AbilityInstance->ResetLifetime();
	AbilityInstance->AfterInitialization();
}