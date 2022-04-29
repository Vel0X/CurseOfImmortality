// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RangedAbility.h"
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
	virtual void AbilityCreationCallback(ABaseAbility* Caller) override;

protected:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> HitActors;

	UPROPERTY(EditAnywhere)
	AActor* Target;
	UPROPERTY(EditAnywhere)
	float BounceRange = 1000;

	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;
};
