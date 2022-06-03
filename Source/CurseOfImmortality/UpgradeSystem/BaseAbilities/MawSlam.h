// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "MawSlam.generated.h"

class USphereComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AMawSlam : public ABaseAbility
{
	GENERATED_BODY()
	// Sets default values for this actor's properties
	AMawSlam();

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystem;

public:
	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;
};
