// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "SeaOfDarkness.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ASeaOfDarkness : public ABaseAbility
{
	GENERATED_BODY()

	ASeaOfDarkness();
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

public:
	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;

private:
	float CurrentScale = 0.f;
};
