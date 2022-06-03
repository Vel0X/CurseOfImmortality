// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "ArcaneReplicatorTurret.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AArcaneReplicatorTurret : public ABaseAbility
{
	GENERATED_BODY()

public:
	AArcaneReplicatorTurret();

	virtual void Tick(float DeltaSeconds) override;

	void SetDirection(FVector Direction);
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	float Speed = 5.0f;
	
};
