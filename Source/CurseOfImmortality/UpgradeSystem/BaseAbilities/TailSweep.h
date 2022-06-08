// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "TailSweep.generated.h"

class USphereComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ATailSweep : public ABaseAbility
{
	GENERATED_BODY()
	
	ATailSweep();

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	float DamageWindow = 0.25f;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;
};

