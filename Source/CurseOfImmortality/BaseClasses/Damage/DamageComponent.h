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
 
 */

class ABaseCharacter;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UDamageComponent();

	UPROPERTY(EditAnywhere)
	TArray<FComponentReference> DamagingHitboxReferences;

	UPROPERTY(EditAnywhere)
	TArray<UDamageSpecification*> DamagingHitboxDamageSpecifications;
	
	UPROPERTY()
	TMap<UPrimitiveComponent*, UDamageObject*> DamagingHitboxes;

	UPROPERTY(EditAnywhere)
	TArray<UDamageSpecification*> DirectDamageSpecifications;

	UPROPERTY()
	TArray<UDamageObject*> DirectDamageObjects;
	
	void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ConvertInterface();

	UFUNCTION(BlueprintCallable)
	bool OnCharacterHit(const UPrimitiveComponent* DamageComponentOverlap, ABaseCharacter* HitCharacter);

	//manually trigger a damage object
	void DirectCharacterHit(int Index, ABaseCharacter* HitCharacter);

	/**
	 * Set the DamageObject of a DamagingHitbox using a DamageObject
	 */
	UFUNCTION(BlueprintCallable)
	void SetupDamagingComponentByDamageObject(UPrimitiveComponent* Component, UDamageObject* DamageObject);

	/**
	 * Set the DamageObject of a DamagingHitbox using a DamageSpecifcation
	 */
	UFUNCTION(BlueprintCallable)
	void SetupDamagingComponentByDamageSpecification(UPrimitiveComponent* Component, UDamageSpecification* DamageSpecification);

	/**
	 * Set the DamageObject of a DamagingHitbox using a DamageSpecifcation
	 */
	UFUNCTION(BlueprintCallable)
	void SetupDamagingComponentByIndexAndDamageSpecification(int Index, UDamageSpecification* DamageSpecification);
	
	/**
	 * Reset Hit Character Lists for all Damaging Components
	 */
	UFUNCTION(BlueprintCallable)
	void ResetAllHitCharacters();

	/**
	 * Reset Hit Character Lists for a single Damaging Component
	 */
	UFUNCTION(BlueprintCallable)
	void ResetHitCharactersForHitbox(UPrimitiveComponent* Hitbox);

	UFUNCTION(BlueprintCallable)
	void ResetHitCharactersForHitboxByIndex(int Index);
	
	/**
	 * Toggle a Hitbox using a reference to the component
	 */
	UFUNCTION(BlueprintCallable)
	void ToggleHitbox(UPrimitiveComponent* Hitbox);

	/**
	 * Toggle a Hitbox using an Index into the DamagingHitboxReferences Array
	 */
	UFUNCTION(BlueprintCallable)
	void ToggleHitboxByIndex(int Index);

	void SetDamageObjectOwner(UDamageObject* DamageObject) const;
};

