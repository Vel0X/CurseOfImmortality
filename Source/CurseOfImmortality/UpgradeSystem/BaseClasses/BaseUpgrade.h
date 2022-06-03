// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "BaseUpgrade.generated.h"

class ARangedAbility;
class ABaseCharacter;
class AChar;
class ABaseAbility;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURSEOFIMMORTALITY_API UBaseUpgrade : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseUpgrade();

	virtual void InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel);
	
	UFUNCTION()
	virtual void OnAbilityStart();

	UFUNCTION()
	virtual void OnAbilityEnd();

	UFUNCTION()
	virtual void OnEnemyHit(ABaseCharacter* Enemy);

	UFUNCTION()
	virtual void OnAbilityHit(ARangedAbility* Ability);
	
	TEnumAsByte<EAbilityType> RestrictedTo;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	ABaseAbility* AbilityInstance;

	UPROPERTY(EditAnywhere)
	int Level;

		
};
