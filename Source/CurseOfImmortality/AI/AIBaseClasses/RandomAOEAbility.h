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

	FVector GetAttackLocation(FVector PlayerLocation) const;

private:
	UPROPERTY(EditAnywhere)
	float RangeAroundPlayer = 500.f;
	UPROPERTY(EditAnywhere)
	float Amount = 1.f;
};
