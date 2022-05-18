#include "ObjectFactory.h"
#include "PersistentWorldManager.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageObject.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/BuffSpecification.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/DamageSpecification.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/UpgradeList.h"

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
	UBuffSpecification* Specification = PossibleUpgrades->Buffs[BuffName];
	UBaseBuff* BuffInstance = NewObject<UBaseBuff>(Specification->Class->StaticClass(), Specification->Class);
	BuffInstance->SetupBuff(Specification);
	return BuffInstance;	
}

UDamageObject* AObjectFactory::GetDamageObject(UDamageSpecification* Specification) const
{
	UDamageObject* DamageObjectInstance = NewObject<UDamageObject>(Specification->Class->StaticClass(), Specification->Class);
	DamageObjectInstance->SetupDamageObject(Specification);
	return DamageObjectInstance;
}

