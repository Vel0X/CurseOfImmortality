// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "DataAssets/AbilitySpecification.h"
#include "GameFramework/Actor.h"
#include "BaseAbility.generated.h"

class UDamageComponent;
class ABaseCharacter;
class AChar;
class UBaseUpgrade;



UCLASS()
class CURSEOFIMMORTALITY_API ABaseAbility : public AActor
{
	GENERATED_BODY()

public:
	ABaseAbility();

	virtual void OnAbilityCreation();
protected:
	virtual void BeginPlay() override;


public:
	void CheckCollisions();
	void OnCharacterHit(ABaseCharacter* OverlappingCharacter);
	virtual void Tick(float DeltaTime) override;
	virtual void DestroyAbility();
	virtual void InitializeAbility(ABaseCharacter* _Caster, int Level, const UAbilitySpecification* Specification);
	virtual void AfterInitialization();

	UPROPERTY(EditAnywhere)
	ABaseCharacter* Caster;
	UPROPERTY(EditAnywhere)
	float AbilityLifetime = 3.0f;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAbilityType> AbilityType;
	void AddUpgrade(const TSubclassOf<UBaseUpgrade>& Class, int UpgradeLevel);
	void ResetLifetime();
	bool DestroyOnEnemyHit = false;
	bool CanInteract = false;
	bool NoFaction = false;
	UPROPERTY(EditAnywhere)
	float RelativeSize = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int AbilityLevel = 1;
	
	int AbilityHandle = -1;

	UPROPERTY(EditAnywhere)
	bool IgnoreInitialCollisions = false;

	//Sound Keys
	FString CastSound;
	FString EnemyHitSound;
	FString WallHitSound;

	UPROPERTY(EditAnywhere)
	UDamageComponent* DamageComponent;
protected:
	UPROPERTY(EditAnywhere)
	TArray<UBaseUpgrade*> UpgradeStack;
	float RemainingAbilityLifetime;

	UPROPERTY()
	UNiagaraSystem* DestructionVfx;

private:
	FScriptDelegate OverlapDelegate;

	UPROPERTY(EditAnywhere)
	TArray<UPrimitiveComponent*> HitBoxes;

	UPROPERTY(EditAnywhere)
	TArray<ABaseCharacter*> InitialCollisions;
};
