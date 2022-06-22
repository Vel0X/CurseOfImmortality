// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "LaserBeam.generated.h"

class UNiagaraComponent;
UCLASS()
class CURSEOFIMMORTALITY_API ALaserBeam : public ABaseAbility
{
	GENERATED_BODY()

public:
	ALaserBeam();

protected:
	virtual void BeginPlay() override;

	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void DestroyAbility() override;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	float SpawnInterval = 0.5f;

private:
	float TimeUntilNextSpawn = 0.0f;
	int Handle = -1;
};
