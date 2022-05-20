#include "ObjectFactory.h"
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

ABaseCharacter* AObjectFactory::SpawnCharacter(const EEnemy Character, const FVector Location, const FRotator Rotation) const
{
	
	if(!Spawnables->Enemies.Contains(Character))
	{
		UE_LOG(LogTemp, Error, TEXT("Character exists in EEnemy, but not in Spawnables List"));
		return nullptr;
	}

	const TSubclassOf<ABaseCharacter> CharacterClass = Spawnables->Enemies[Character];

	if(CharacterClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Character has no Specification set in Spawnables List"));
		return nullptr;
	}

	ABaseCharacter* CharacterInstance = Cast<ABaseCharacter>(GetWorld()->SpawnActor(CharacterClass, &Location, &Rotation));
	return CharacterInstance;
}

ABaseAbility* AObjectFactory::SpawnAbility(EUpgradeName Ability, const FVector Location, const FRotator Rotation) const
{
}
