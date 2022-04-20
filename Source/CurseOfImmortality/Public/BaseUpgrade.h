// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "GameFramework/Actor.h"
#include "BaseUpgrade.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API ABaseUpgrade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseUpgrade();
	
	void InitializeUpgrade(ABaseAbility* abilityInstance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnAbilityStart();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
