// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "CurseOfImmortality/Enemies/EnemySpecification.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "GameFramework/Actor.h"
#include "ObjectFactory.generated.h"

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

	virtual void BeginPlay() override;

	UEnemySpecification* GetSpecification(EEnemy Enemy) const;

	UAssortmentSpecification* GetSpecification(EAssortment Assortment) const;

	UFUNCTION(BlueprintCallable)
	UBaseBuff* GetBuff(EBuff BuffName) const;

	UFUNCTION(BlueprintCallable)
	UDamageObject* GetDamageObject(const UDamageSpecification* Specification) const;

	UFUNCTION(BlueprintCallable)
	ABaseEnemyPawn* SpawnEnemyCustomSpawnBehaviour(EEnemy Character) const;
	
	UFUNCTION(BlueprintCallable)
	ABaseEnemyPawn* SpawnEnemy(EEnemy Character, const FVector Location, const FRotator Rotation) const;

	UFUNCTION(BlueprintCallable)
	ABaseAbility* SpawnAbility(EUpgradeName Ability, const FVector Location, const FRotator Rotation, const ABaseCharacter* Caster) const;
	
	UPROPERTY(EditAnywhere)
	USpawnablesList* Spawnables;
};

