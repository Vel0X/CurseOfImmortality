// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/GameDummy/Char.h"
#include "GameFramework/Actor.h"
#include "BaseAbility.generated.h"

//DECLARE_EVENT_OneParam(ABaseAbility, FOnAbilityStart, int);
//DECLARE_EVENT_OneParam(ABaseAbility, FOnAbilityEnd, int);

class UBaseUpgrade;
UENUM()
enum EAbilityType
{
	None, 
	Melee,
	Ranged,
	Special
};


UCLASS()
class CURSEOFIMMORTALITY_API ABaseAbility : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABaseAbility();
	UFUNCTION(BlueprintCallable)
	virtual void OnEnemyHit(AActor* OverlappedActor, AActor* OtherActor);
	virtual void OnAbilityCreation();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DestroyAbility();

	virtual void InitializeAbility(int _AbilityHandle, AChar* _Caster, int Level);

	virtual void AfterInitialization();

public:
	UPROPERTY(EditAnywhere)
	AChar* Caster;
	UPROPERTY(EditAnywhere)
	float AbilityLifetime = 3.0f;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAbilityType> AbilityType;
	void AddUpgrade(const TSubclassOf<UBaseUpgrade>& Class, int UpgradeLevel);
	void ResetLifetime();
	bool DestroyOnEnemyHit = false;
	bool CanInteract = false;
	UPROPERTY(EditAnywhere)
	float RelativeSize = 1.0f;
protected:
	UPROPERTY(EditAnywhere)
	TArray<UBaseUpgrade*> UpgradeStack;
private:
	float RemainingAbilityLifetime;
	int AbilityHandle;
	FScriptDelegate OverlapDelegate;

};
