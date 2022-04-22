// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseUpgrade.h"
#include "BaseAbility.h"


#include "AttackManager.generated.h"

/// <summary>
/// A currently active Ability with a stack of upgrades attached to it 
/// </summary>

struct FActiveAbility
{
	FActiveAbility(ABaseAbility* _AbilityInstance, TArray<UBaseUpgrade*> _ActiveUpgrades) : AbilityInstance(_AbilityInstance), ActiveUpgrades(_ActiveUpgrades) {}

	ABaseAbility* AbilityInstance;
	TArray<UBaseUpgrade*> ActiveUpgrades;
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
	void CleanupAbility(int AbilityHandle);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnKeyPressed();
	void BindToInput();
	void SpawnFromTemplate(ABaseAbility* Template) const;
	void SpawnFromTemplate(ABaseAbility* Template, FRotator Rotator) const;

	
public:
	//ActiveAbility activeAbility;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseAbility>  abilityClassType;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UBaseUpgrade>> Upgrades;

private:
	int AbilityMapHandle;
	TMap<int, FActiveAbility> ActiveAbilities;
};

