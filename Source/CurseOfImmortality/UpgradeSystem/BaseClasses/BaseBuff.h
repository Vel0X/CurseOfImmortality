// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "BaseBuff.generated.h"

class AChar;

UCLASS()
class CURSEOFIMMORTALITY_API UBaseBuff : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseBuff();
	
	UFUNCTION()
	virtual void OnTakeDamage(int AbilityHandle);

	virtual void OnBuffBegin();

	virtual void OnBuffTick(float DeltaTime);
	
	virtual void OnBuffEnd();

	virtual void IntitializeBuff(int Level, AChar* _Owner);

public:

	UPROPERTY(EditAnywhere)
	AChar* Owner;
	
	UPROPERTY(EditAnywhere)
	float BuffDuration;

	float RemainingDuration;
	
	//when this buff is already on an object multiple iterations can be stacked atop of each other
	UPROPERTY(EditAnywhere)
	bool Stackable;
	
	UPROPERTY(EditAnywhere)
	int CurrentStacks;

	//ignore BuffDuration and instead remove the Buff at an arbitrary point in time
	UPROPERTY(EditAnywhere)
	bool CustomBuffEnd;

	UPROPERTY(EditAnywhere)
	bool StatModifier;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> StatModifications; 
};
