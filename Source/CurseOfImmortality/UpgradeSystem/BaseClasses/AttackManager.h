// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurseOfImmortality/Enemies/ArcaneReplicator/ArcaneReplicatorCrab.h"
#include "DataAssets/SpawnablesList.h"
#include "DataAssets/UpgradeSpecification.h"
#include "AttackManager.generated.h"


class UUpgradeSpecification;
class UAbilitySpecification;


UCLASS(BlueprintType)
class UDisplayInformation : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Application;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture* Image;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Level = 1;
};

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
	FPooledEntry(): Name(), CurrentLevel(0), Type(false), Weight(0)
	{
	}

	FPooledEntry(const TEnumAsByte<EUpgradeName>& Name, const int CurrentLevel, const bool bType, const int Weight)
		:  Name(Name),
		CurrentLevel(CurrentLevel),
		  Type(bType),
		  Weight(Weight)
	{
	}
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EUpgradeName> Name;

	UPROPERTY(EditAnywhere)
	int CurrentLevel;

	UPROPERTY(EditAnywhere)
	bool Type; //false = Ability, true = Upgrade

	UPROPERTY(EditAnywhere)
	int Weight;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API UAttackManager : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UAttackManager();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnKeyPressed(EAbilityType Type, FVector SpawnLocation);
	
	void SortActiveUpgrades(bool Verbose = false);
	
	bool CheckCooldown(EAbilityType Ability);
	
	void SpawnAbility(FActiveAbility& Ability, FVector SpawnLocation);

	void SpawnAbility(FActiveAbility& Ability, FVector Position, FRotator Rotation);
	
	UFUNCTION(BlueprintCallable)
	void SpawnAbility(EAbilityType Ability);

	UFUNCTION(BlueprintCallable)
	void SpawnAbilityRotationSpecified(EAbilityType Ability, FVector Position, FRotator Rotation);
	
	void SpawnFromTemplate(ABaseAbility* Template) const;
	void SpawnFromTemplate(ABaseAbility* Template, FVector Position, FRotator Rotator) const;

	/**
	 * @brief
	 * Creates a pool of Upgrades, from which three can be picked with weighted possibilities. The pool and the weights are dependent on which upgrades and how many of them the player already has
	 */
	void UpdateAbilityPool();

	UFUNCTION(BlueprintCallable, Category="AttackManager")
	void PickThreeFromPool(bool Verbose = false);

	UFUNCTION(BlueprintCallable)
	TArray<UDisplayInformation*> GetUpgradeDisplayInformation();

	void AddDisplayInformation(TArray<UDisplayInformation*>& List, FString Name, FText Application, FText Description, UTexture2D* Texture, int Level) const;

	UFUNCTION(BlueprintCallable)
	void GetActivesDisplayInformation(TMap<TEnumAsByte<EAbilityType>, UDisplayInformation*>& ActiveBaseAbilities, TArray<UDisplayInformation*>& ActiveUpgrades);

	static FText GetAbilityApplication(EAbilityType Type);

	static FText GetUpgradeApplication(EAbilityType Type);

	UFUNCTION(BlueprintCallable, Category="AttackManager")
	void GetUpgrade(int Index);

	void PrintCurrentlyActive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EAbilityType>, FActiveAbility> ActiveAbilities;
	
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EUpgradeName>, FActiveUpgrade> ActiveUpgrades;

	
	UPROPERTY(EditAnywhere)
	USpawnablesList* PossibleUpgrades;

	UPROPERTY(EditAnywhere)
	TArray<FPooledEntry> Pool;

	//Indizes to three entries from Pool, selected using PickThreeFromPool
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int> SelectedPoolEntries;

	//Blueprint Actors, that get spawned with Upgrades need to be defined in an actor, since the BP-Assets can only be assigned via UI
	UPROPERTY(EditAnywhere)
	TSubclassOf<AArcaneReplicatorCrab> ArcaneReplicatorTurretBP;
	
	//UPROPERTY(EditAnywhere)
	//TMap<TEnumAsByte<EAbilityType>, float> Cooldowns = TMap<TEnumAsByte<EAbilityType>, float>();
};

