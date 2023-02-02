// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIDamageObject.generated.h"

class USphereComponent;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API UAIDamageObject : public UActorComponent
{
	GENERATED_BODY()

	void DealDamageToPawns() const;

public:
	// Sets default values for this component's properties
	UAIDamageObject();
	void SetUp(float _Duration, bool bNoDot, float _DamageRadius, FVector _SpawnLocation, float _Damage);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Duration = 0.f;
	float DamageRadius = 0.f;
	float Damage = 0.f;
	bool NoDot = false;
	bool SetupComplete= false;

	FVector SpawnLocation = FVector::ZeroVector;

	UPROPERTY()
	USphereComponent* DamageSphere = nullptr;
};
