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
	
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;
};


