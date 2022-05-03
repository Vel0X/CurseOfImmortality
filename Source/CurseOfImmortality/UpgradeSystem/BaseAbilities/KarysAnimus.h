// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/SpecialAbility.h"
#include "GameFramework/Actor.h"
#include "KarysAnimus.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API AKarysAnimus : public ASpecialAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKarysAnimus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void AnimatePosition(float DeltaTime);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	float PassedTime = 0.0f, LastSineDelta = 0.0f, TimeUntilNextSpawn = 0.0f;

	UPROPERTY(EditAnywhere)
	float SpawnInterval = 0.5f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseAbility> ProjectileClass;
};
