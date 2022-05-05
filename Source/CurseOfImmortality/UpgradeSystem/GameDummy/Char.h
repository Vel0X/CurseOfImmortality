// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "Char.generated.h"


class UBaseStatSpecification;
UCLASS()
class CURSEOFIMMORTALITY_API AChar : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RecalculateStats();

	void AddBuff(UBaseBuff* Buff);
	
	void RemoveBuff(UBaseBuff* Buff);
	void TakeDamage(float Amount, bool Verbose = false);
	
	UPROPERTY(EditAnywhere)
	TArray<UBaseBuff*> Buffs;

	float CurrentHealth = 0.0f;
	
	UPROPERTY(EditAnywhere)
	UBaseStatSpecification* BaseStats;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> Stats;
	//TArray<>
};

