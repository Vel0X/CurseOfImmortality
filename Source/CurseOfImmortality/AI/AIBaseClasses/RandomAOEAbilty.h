// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RandomAOEAbilty.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API URandomAOEAbilty : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URandomAOEAbilty();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void StartAbility();

private:
	float DamageField = 100.f;
	float RangeAroundPlayer = 500.f;
	float DamageDuration = 1.f;
	float Damage = 10.f;
};
