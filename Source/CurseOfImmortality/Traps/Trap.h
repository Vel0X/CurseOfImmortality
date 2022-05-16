// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "Trap.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ATrap : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ATrap();

protected:
	
	virtual void Setup() override;

public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void DealDamage(float Damage, ABaseCharacter *EnemyCharacter) override;
};
