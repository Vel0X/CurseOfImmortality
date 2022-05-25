// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "BaseEnemyPawn.generated.h"

class UEnemySpecification;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ABaseEnemyPawn : public ABaseCharacter
{
	GENERATED_BODY()


public:
	virtual bool GetSpawnPosition(FVector& Position, FRotator& Rotation);

	void Init(const UEnemySpecification* Specification);
	
	UPROPERTY(EditAnywhere)
	int PowerLevel;
};
