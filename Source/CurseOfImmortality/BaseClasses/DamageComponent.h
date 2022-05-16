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

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UDamageComponent();

	UPROPERTY(EditAnywhere)
	TMap<UShapeComponent*, UDamageObject*> DamagingComponents;
	
	void SetupDamageComponent(UShapeComponent* Component, UDamageObject* DamageObject);
};
