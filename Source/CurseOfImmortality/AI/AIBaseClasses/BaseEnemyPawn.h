// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseEnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ABaseEnemyPawn : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABaseEnemyPawn();

private:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CollisionCapsule;

	//Getter
public:
	UCapsuleComponent* GetCollisionCapsule() const;
};
