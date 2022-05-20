// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "GameFramework/Actor.h"
#include "ObjectFactory.generated.h"

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

	UBaseBuff* GetBuff(EBuff BuffName) const;

	UDamageObject* GetDamageObject(const UDamageSpecification* Specification) const;

	ABaseCharacter* SpawnCharacter(EEnemy Character, const FVector Location, const FRotator Rotation) const;

	ABaseAbility* SpawnAbility(EUpgradeName Ability, const FVector Location, const FRotator Rotation) const;
	
	UPROPERTY(EditAnywhere)
	USpawnablesList* Spawnables;
};

