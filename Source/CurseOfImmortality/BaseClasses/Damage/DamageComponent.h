// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageObject.h"
#include "DamageComponent.generated.h"


/**
 * When any Component of any actor hits any Component of this Actor, then this Component should get notified.
 * (With correct Setup only Collider-Components on this Actor should have OnOverlap enabled and )
 *
 *
 *
 *
 *
 *
 *
 */

class ABaseCharacter;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UDamageComponent();

	UPROPERTY(EditAnywhere)
	TArray<FComponentReference> References;

	UPROPERTY(EditAnywhere)
	TArray<UDamageSpecification*> DamageObjects;
	
	UPROPERTY(EditAnywhere)
	TMap<UPrimitiveComponent*, UDamageObject*> DamagingComponents;
	
	void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ConvertInterface();

	UFUNCTION(BlueprintCallable)
	void OnCharacterHit(const UPrimitiveComponent* DamageComponentOverlap, ABaseCharacter* HitCharacter);

	
	void SetupDamageComponent(UPrimitiveComponent* Component, UDamageObject* DamageObject);

	void ResetAllHitCharacters();
};
