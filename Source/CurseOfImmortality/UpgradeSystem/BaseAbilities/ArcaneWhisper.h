// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/RangedAbility.h"
#include "ArcaneWhisper.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AArcaneWhisper : public ARangedAbility
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void AfterInitialization() override;
	virtual void OnAbilityCreation() override;
	virtual void InitializeAbility(int _AbilityHandle, AChar* Caster, int Level) override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
	AActor* Target;
	UPROPERTY(EditAnywhere)
	float BounceRange = 700;

	bool delayedAfterInit = false;
	UPROPERTY(EditAnywhere)
	FVector SpawnLocation = FVector::Zero();
};
