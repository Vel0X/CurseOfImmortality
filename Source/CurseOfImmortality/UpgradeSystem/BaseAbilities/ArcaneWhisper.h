// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/RangedAbility.h"
#include "ArcaneWhisper.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AArcaneWhisper final : public ARangedAbility
{
	GENERATED_BODY()

public:
	AArcaneWhisper();

	
	virtual void BeginPlay() override;
	virtual void AfterInitialization() override;
	virtual void OnAbilityCreation() override;
	virtual void InitializeAbility(ABaseCharacter* Caster, int Level, const UAbilitySpecification* Specification) override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
	ABaseCharacter* Target;
	UPROPERTY(EditAnywhere)
	float BounceRange = 2000;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystem;
	
	bool DelayedInitPending = false;
};
