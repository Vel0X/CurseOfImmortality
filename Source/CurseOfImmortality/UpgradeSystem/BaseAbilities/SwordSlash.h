﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/MeleeAbility.h"
#include "SwordSlash.generated.h"

class USphereComponent;
class UNiagaraComponent;
UCLASS()
class CURSEOFIMMORTALITY_API ASwordSlash final : public AMeleeAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwordSlash();

public:
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystem;
	UPROPERTY(EditAnywhere)
	USphereComponent* Collision;
};