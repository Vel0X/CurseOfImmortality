// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAbility.h"
#include "BaseUpgrade.h"


#include "AttackManager.generated.h"

/// <summary>
/// A currently active Ability with a stack of upgrades attached to it 
/// </summary>
class ActiveAbility
{
public:
	float x;
private:
	float y;
};


UCLASS()
class CURSEOFIMMORTALITY_API AAttackManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnKeyPressed();
	void BindToInput(); 
	
public:
	ActiveAbility activeAbility;

	UPROPERTY(EditAnywhere)
	ABaseAbility* meleeAbility;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseAbility>  abilityClassType;

	UPROPERTY(EditAnywhere)
	ABaseUpgrade* sealOfCongruenceUpgrade;
private:
	ABaseAbility* abilityInstance;

};

