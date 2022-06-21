// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/RangedAbility.h"
#include "TrapProjectile.generated.h"

class USphereComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ATrapProjectile : public ARangedAbility
{
	GENERATED_BODY()

	ATrapProjectile();
	
protected:
	virtual void Tick(float DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* Trail;
	UPROPERTY(EditAnywhere)
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
	float Speed = 20.0f;
};
