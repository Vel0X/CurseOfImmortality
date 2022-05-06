// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
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
	void AddBuffParticles(UBaseBuff* Buff);
	void RemoveBuffParticles(const UBaseBuff* Buff);
	void TakeDmg(float Amount, bool Verbose = false);
	void Heal(float Amount, bool Verbose = false);

	UPROPERTY(EditAnywhere)
	TArray<UBaseBuff*> Buffs;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EBuff>, UNiagaraComponent*> ActiveParticleEffects;
	
	float CurrentHealth = 0.0f;
	
	UPROPERTY(EditAnywhere)
	UBaseStatSpecification* BaseStats;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> Stats;

	UPROPERTY(EditAnywhere)
	FString DisplayName = "";
	//TArray<>
};


