// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "GameFramework/Actor.h"
#include "ObjectFactory.generated.h"

class UDamageObject;
class UDamageSpecification;
class UUpgradeList;
UCLASS()
class CURSEOFIMMORTALITY_API AObjectFactory : public AActor
{
	GENERATED_BODY()

public:
	AObjectFactory();

	virtual void BeginPlay() override;

	UBaseBuff* GetBuff(EBuff BuffName) const;

	UDamageObject* GetDamageObject(UDamageSpecification* Specification) const;

	UPROPERTY(EditAnywhere)
	UUpgradeList* PossibleUpgrades;
};

