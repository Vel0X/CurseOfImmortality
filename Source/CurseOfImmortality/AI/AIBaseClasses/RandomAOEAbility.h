// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "RandomAOEAbility.generated.h"

class UAbilitySpecification;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API URandomAOEAbility : public UActorComponent
{
	GENERATED_BODY()

public:
	void StartAbility(UAbilitySpecification* AbilitySpecification, ABaseCharacter* Caster);

private:
	UPROPERTY(EditAnywhere)
	float DamageField = 100.f;
	UPROPERTY(EditAnywhere)
	float RangeAroundPlayer = 500.f;
	UPROPERTY(EditAnywhere)
	float DamageDuration = 10.f;
	UPROPERTY(EditAnywhere)
	float Damage = 10.f;
	UPROPERTY(EditAnywhere)
	float Amount = 3.f;
};
