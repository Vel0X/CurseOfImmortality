// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "BaseBuff.generated.h"

class AChar;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API UBaseBuff : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseBuff();

	virtual void InitializeBuff(AChar* _Target);
	
	UFUNCTION()
	virtual void OnTakeDamage(int AbilityHandle);

	virtual void OnBuffBegin();

	virtual void OnBuffTick(float DeltaTime);
	
	virtual void OnBuffEnd();

	virtual void IntitializeBuff(int Level);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	AChar* Target;
	
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
