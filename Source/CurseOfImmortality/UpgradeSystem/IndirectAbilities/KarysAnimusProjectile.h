// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/RangedAbility.h"
#include "KarysAnimusProjectile.generated.h"

class USphereComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AKarysAnimusProjectile : public ARangedAbility
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AKarysAnimusProjectile();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	bool GetTarget();
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* Trail;
	UPROPERTY(EditAnywhere)
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
	float MaxRange = 100000.0f;
	UPROPERTY(EditAnywhere)
	float SpawnAngleVariation = 1.0f;
	UPROPERTY(EditAnywhere)
	float Speed = 100.0f;
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 30.0f;
	UPROPERTY()
	USceneComponent* Target;
};

