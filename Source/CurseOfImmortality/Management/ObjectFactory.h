// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "GameFramework/Actor.h"
#include "ObjectFactory.generated.h"

class ABaseCharacter;
class ADamageIndicator;
class ABaseAbility;
class ABaseEnemyPawn;
class UAssortment;
class UBaseBuff;
class UBuffSpecification;
class UEnemySpecification;
class URound;
class UAssortmentSpecification;
class UDamageObject;
class UDamageSpecification;
class USpawnablesList;

UCLASS()
class CURSEOFIMMORTALITY_API AObjectFactory : public AActor
{
	GENERATED_BODY()

public:
	AObjectFactory();
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
	//retrieve Specifications based on enums
	UEnemySpecification* GetSpecification(EEnemy Enemy) const;
	UAssortmentSpecification* GetSpecification(EAssortment Assortment) const;
	UBuffSpecification* GetSpecification(EBuff Buff) const;

			///////////////////////////////////
			///--------spawn uObjects----------
			///////////////////////////////////
	
	UFUNCTION(BlueprintCallable)
	UBaseBuff* GetBuff(EBuff BuffName) const;

	UFUNCTION(BlueprintCallable)
	UDamageObject* GetDamageObject(const UDamageSpecification* Specification) const;
	
	UFUNCTION(BlueprintCallable)
	URound* GetRound(const int Index) const;

	/**
	 * @brief  Spawn an Assortment using the Enumerator. (Note: The Enemies contained in the Assortment have to be spawned seperately using SpawnEnemies() in the Assortment itself)
	 */
	UFUNCTION(BlueprintCallable)
	UAssortment* SpawnAssortment(EAssortment Assortment) const;

			///////////////////////////////////
			///--------spawn actors------------
			///////////////////////////////////
			
	/**
	 * @brief Spawn an Enemy using the specified SpawnBehaviour defined within the enemy
	 */
	UFUNCTION(BlueprintCallable)
	ABaseEnemyPawn* SpawnEnemyCustomSpawnBehaviour(EEnemy Character) const;
	
	/**
	 * @brief Spawn an Enemy at a specific Location with a specific Rotation
	 */
	UFUNCTION(BlueprintCallable)
	ABaseEnemyPawn* SpawnEnemy(EEnemy Character, const FVector Location, const FRotator Rotation) const;
	
	UFUNCTION(BlueprintCallable)
	ABaseAbility* SpawnAbility(EUpgradeName Ability, const FVector Location, const FRotator Rotation, const ABaseCharacter* Caster) const;

	ADamageIndicator* SpawnDamageIndicator(FString Text, FColor Color, const FVector Location, const FRotator Rotation) const;

	UAudioComponent* SpawnSound();
	
	/**
	 * @brief DataAsset containing all of the Spawnable Actors, Components and UObjects. Should not be accessed directly, but using the object-specific functions
	 */
	UPROPERTY(EditAnywhere)
	USpawnablesList* Spawnables;
};

