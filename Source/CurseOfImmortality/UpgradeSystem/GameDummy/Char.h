// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseStatSpecification.h"
#include "Char.generated.h"



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
	
	UPROPERTY(EditAnywhere)
	TArray<UBaseBuff*> Buffs;
	
	UPROPERTY(EditAnywhere)
	UBaseStatSpecification* BaseStats;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> Stats;
	//TArray<>
};
