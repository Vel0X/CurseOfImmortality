// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "Components/ActorComponent.h"
#include "BaseUpgrade.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURSEOFIMMORTALITY_API UBaseUpgrade : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseUpgrade();

	void InitializeUpgrade(ABaseAbility* _AbilityInstance);
	
	UFUNCTION()
	virtual void OnAbilityStart(int AbilityHandle);

	UFUNCTION()
	virtual void OnAbilityEnd(int AbilityHandle);

	TEnumAsByte<EAbilityType> RestrictedTo;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	ABaseAbility* AbilityInstance;

		
};
