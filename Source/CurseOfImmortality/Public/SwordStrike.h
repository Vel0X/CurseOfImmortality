// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "SwordStrike.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ASwordStrike : public ABaseAbility
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
