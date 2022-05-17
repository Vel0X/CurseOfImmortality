// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/SpecialAbility.h"
#include "Whirlwind.generated.h"

class USphereComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AWhirlwind final : public ASpecialAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWhirlwind();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;
};
