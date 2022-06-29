// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "DolomarsWrath.generated.h"

class USphereComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ADolomarsWrath : public ABaseAbility
{
	GENERATED_BODY()
	// Sets default values for this actor's properties
	ADolomarsWrath();
	virtual void Tick(float DeltaSeconds) override;

	float CurrentScale = 0.f;

	bool Active = false;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystem;

public:
	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;

private:
	float Duration = 0.75f;
	float DamageDuration = 0.1f;
};
