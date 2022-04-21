// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAbility.generated.h"

DECLARE_EVENT_OneParam(ABaseAbility, FOnAbilityStart, int);
DECLARE_EVENT_OneParam(ABaseAbility, FOnAbilityEnd, int);

UENUM()
enum EAbilityType
{
	Melee,
	Ranged,
	Skill
};


UCLASS()
class CURSEOFIMMORTALITY_API ABaseAbility : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ABaseAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitializeAbility(int _AbilityHandle);
	void AfterInitialization() const;

public:
	UPROPERTY(EditAnywhere)
	float AbilityLifetime = 3.0f;
	FOnAbilityStart OnAbilityStart;
	FOnAbilityEnd OnAbilityEnd;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAbilityType> AbilityType;
private:
	float RemainingAbilityLifetime;
	int AbilityHandle;

};
