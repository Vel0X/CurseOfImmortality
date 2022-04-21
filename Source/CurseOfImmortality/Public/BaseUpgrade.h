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
	
	void InitializeUpgrade(ABaseAbility* _AbilityInstance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnAbilityStart(int AbilityHandle);

	UFUNCTION()
	virtual void OnAbilityEnd(int AbilityHandle);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TEnumAsByte<EAbilityType> RestrictedTo;

protected:
	UPROPERTY(EditAnywhere)
	ABaseAbility* AbilityInstance;


};
