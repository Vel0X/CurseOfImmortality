// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeSpecification.h"
#include "../../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/clsocket/src/ActiveSocket.h"
#include "CurseOfImmortality/UpgradeSystem/IndirectAbilities/ArcaneReplicatorTurret.h"
#include "GameFramework/Actor.h"
#include "AttackManager.generated.h"


class UUpgradeSpecification;
class UAbilitySpecification;

USTRUCT()
struct FActiveAbility
{
	GENERATED_BODY()

	FActiveAbility(): Specification(nullptr), Level(1), CurrentCooldown(0.0f)
	{
	}

	FActiveAbility(UAbilitySpecification* Specification, const int Level)
		:Specification(Specification), Level(Level), CurrentCooldown(0.0f)
	{
	}
	
	UPROPERTY(EditAnywhere)
	UAbilitySpecification* Specification;
	
	UPROPERTY(EditAnywhere)
	int Level;

	UPROPERTY(EditAnywhere)
	float CurrentCooldown;
};

USTRUCT()
struct FActiveUpgrade
{
	GENERATED_BODY()

	FActiveUpgrade(): Specification(nullptr), Level(1)
	{
	}

	FActiveUpgrade(UUpgradeSpecification* Specification, const int Level)
		:Specification(Specification), Level(Level)
	{
	}
	
	UPROPERTY(EditAnywhere)
	UUpgradeSpecification* Specification;
	
	UPROPERTY(EditAnywhere)
	int Level;

	bool operator<(const FActiveUpgrade& Other) const
	{
		return Specification->UpgradeOrder < Other.Specification->UpgradeOrder;
	}

};

USTRUCT()
struct FPooledEntry
{
	GENERATED_BODY()
	FPooledEntry(): Name(), Type(false), Weight(0)
	{
	}

	FPooledEntry(const TEnumAsByte<EUpgradeName>& Name, const bool bType, const int Weight)
		: Name(Name),
		  Type(bType),
		  Weight(Weight)
	{
	}

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EUpgradeName> Name;

	UPROPERTY(EditAnywhere)
	bool Type; //false = Ability, true = Upgrade

	UPROPERTY(EditAnywhere)
	int Weight;
};

UCLASS()
class CURSEOFIMMORTALITY_API AAttackManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void OnRangedKeyPressed();
	void OnSpecialKeyPressed();
	
	void BindToInput();
	
	void SortActiveUpgrades();
	
	bool CheckCooldown(EAbilityType Ability);
	
	void SpawnAbility(FActiveAbility& Ability);
	void SpawnFromTemplate(ABaseAbility* Template) const;
	void SpawnFromTemplate(ABaseAbility* Template, FRotator Rotator) const;

	/**
	 * @brief
	 * Creates a pool of Upgrades, from which three can be picked with weighted possibilities. The pool and the weights are dependent on which upgrades and how many of them the player already has
	 */
	void UpdateAbilityPool();

	void PickThreeFromPool();

	void GetUpgrade(int Index);

	void PrintCurrentlyActive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CleanupAbility(int AbilityHandle);
	
public:
	//UPROPERTY(EditAnywhere)
	//FActiveAbility ActiveRangedAbility;
	
	//UPROPERTY(EditAnywhere)
	//FActiveAbility  ActiveSpecialAbility;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EAbilityType>, FActiveAbility> ActiveAbilities;
	
	UPROPERTY(EditAnywhere)
	TArray<FActiveUpgrade> ActiveUpgrades;
	
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EUpgradeName>,UUpgradeSpecification*> PossibleUpgrades;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EUpgradeName>,UAbilitySpecification*> PossibleAbilities;

	UPROPERTY(EditAnywhere)
	TArray<FPooledEntry> Pool;

	//Indizes to three entries from Pool, selected using PickThreeFromPool
	UPROPERTY(EditAnywhere)
	TArray<int> SelectedPoolEntries;

	//Blueprint Actors, that get spawned with Upgrades need to be defined in an actor, since the BP-Assets can only be assigned via UI
	UPROPERTY(EditAnywhere)
	TSubclassOf<AArcaneReplicatorTurret> ArcaneReplicatorTurretBP;
private:
	int AbilityMapHandle = 0;

	//UPROPERTY(EditAnywhere)
	//TMap<TEnumAsByte<EAbilityType>, float> Cooldowns = TMap<TEnumAsByte<EAbilityType>, float>();
};

