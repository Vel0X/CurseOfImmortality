﻿#include "ObjectFactory.h"
#include "PersistentWorldManager.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageObject.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/BuffSpecification.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/DamageSpecification.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/SpawnablesList.h"

// Sets default values
AObjectFactory::AObjectFactory()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AObjectFactory::BeginPlay()
{
	Super::BeginPlay();
	FPersistentWorldManager::ObjectFactory = this;
}

UEnemySpecification* AObjectFactory::GetSpecification(const EEnemy Enemy) const
{
	if(Spawnables->Enemies.Contains(Enemy))
		return Spawnables->Enemies[Enemy];

	UE_LOG(LogTemp, Error, TEXT("No Specification defined for Enemy"));
	return nullptr;
}

UAssortmentSpecification* AObjectFactory::GetSpecification(EAssortment Assortment) const
{
	if(Spawnables->Assortments.Contains(Assortment))
		return Spawnables->Assortments[Assortment];

	UE_LOG(LogTemp, Error, TEXT("No Specification defined for Assortment"));
	return nullptr;
}

UBaseBuff* AObjectFactory::GetBuff(const EBuff BuffName) const
{
	if(!Spawnables->Buffs.Contains(BuffName))
	{
		UE_LOG(LogTemp, Error, TEXT("Buff exists in EBuff, but not in Spawnables List"));
		return nullptr;
	}
	
	UBuffSpecification* Specification = Spawnables->Buffs[BuffName];

	if(Specification == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Buff has no Specification set in Spawnables List"));
		return nullptr;
	}
	
	UBaseBuff* BuffInstance = NewObject<UBaseBuff>(Specification->Class->StaticClass(), Specification->Class);
	BuffInstance->SetupBuff(Specification);
	return BuffInstance;	
}

UDamageObject* AObjectFactory::GetDamageObject(const UDamageSpecification* Specification) const
{
	UDamageObject* DamageObjectInstance = NewObject<UDamageObject>(Specification->Class->StaticClass(), Specification->Class);
	DamageObjectInstance->SetupDamageObject(Specification);
	return DamageObjectInstance;
}

URound* AObjectFactory::GetRound(const int Index) const
{
	if(Index >= 0 && Index < Spawnables->RoundSpecifications.Num())
	{
		URound* Round = NewObject<URound>();
		Round->SetupRound(Spawnables->RoundSpecifications[Index]);
		return Round;
	}
	return nullptr;
}

ABaseEnemyPawn* AObjectFactory::SpawnEnemyCustomSpawnBehaviour(const EEnemy Character) const
{
	if(!Spawnables->Enemies.Contains(Character))
	{
		UE_LOG(LogTemp, Error, TEXT("Character exists in EEnemy, but not in Spawnables List"));
		return nullptr;
	}

	const UEnemySpecification* Specification = Spawnables->Enemies[Character];

	if(Specification == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Character has no Specification set in Spawnables List"));
		return nullptr;
	}

	FVector Location = FVector::Zero();
	FRotator Rotation = FRotator::ZeroRotator;
	ABaseEnemyPawn* CharacterInstance = Cast<ABaseEnemyPawn>(GetWorld()->SpawnActor(Specification->Class, &Location, &Rotation));

	CharacterInstance->GetSpawnPosition(Location, Rotation);
	return CharacterInstance;
}

ABaseEnemyPawn* AObjectFactory::SpawnEnemy(const EEnemy Character, const FVector Location, const FRotator Rotation) const
{
	
	if(!Spawnables->Enemies.Contains(Character))
	{
		UE_LOG(LogTemp, Error, TEXT("Character exists in EEnemy, but not in Spawnables List"));
		return nullptr;
	}

	const UEnemySpecification* Specification = Spawnables->Enemies[Character];

	if(Specification == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Character has no Specification set in Spawnables List"));
		return nullptr;
	}

	ABaseEnemyPawn* CharacterInstance = Cast<ABaseEnemyPawn>(GetWorld()->SpawnActor(Specification->Class, &Location, &Rotation));
	return CharacterInstance;
}

ABaseAbility* AObjectFactory::SpawnAbility(EUpgradeName Ability, const FVector Location, const FRotator Rotation, const ABaseCharacter* Caster) const
{
	if(!Spawnables->PossibleBaseAbilities.Contains(Ability))
	{
		UE_LOG(LogTemp, Error, TEXT("Ability exists in EUpgradeName, but not in Spawnables List"));
		return nullptr;
	}

	const UAbilitySpecification* AbilitySpecification = Spawnables->PossibleBaseAbilities[Ability];

	if(AbilitySpecification == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Ability has no Specification set in Spawnables List"));
		return nullptr;
	}	
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(AbilitySpecification->Class, &Location, &Rotation));

	if(AbilityInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Abiltiy could not be spawned!"));
		return nullptr;
	}
	//AbilityInstance->InitializeAbility(0, static_cast<ABaseCharacter*>(GetOwner()), Ability.Level);
	//AbilityInstance->OnAbilityCreation();
	//AbilityInstance->AbilityType
	return AbilityInstance;
}
