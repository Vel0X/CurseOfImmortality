// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "MawOfSothrosStateMachine.generated.h"

class APlayerCharacter;
class AMawOfSothrosPawn;
/**
 * 
 */

USTRUCT()
struct FAttackType
{
	GENERATED_BODY()

	FAttackType()
	{
		Weight = 400;
		CurrentWeight = Weight;
		Type = VomitState;

		UE_LOG(LogTemp, Warning, TEXT("Wrong Cunstructor in FAttackType"))
	}

	FAttackType(EMawAttacks Type, int Weight): Type(Type), Weight(Weight)
	{
		CurrentWeight = Weight;
	}

	EMawAttacks Type;
	int Weight;
	int CurrentWeight;

	void ResetWeight()
	{
		CurrentWeight = Weight;
	}
};

UCLASS()
class CURSEOFIMMORTALITY_API UMawOfSothrosStateMachine : public UStateMachine
{
	GENERATED_BODY()

	UMawOfSothrosStateMachine();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void Move(float Speed) const;
	void FocusOnPlayer(float DeltaTime, float Speed) const;

	float CalculateAngleBetweenVectors(FVector VectorOne, FVector VectorTwo) const;

	//States
	UPROPERTY()
	UState* Start;
	UPROPERTY()
	UState* Idle;
	UPROPERTY(BlueprintReadOnly)
	UState* Vomit;
	UPROPERTY()
	UState* GroundSlam;
	UPROPERTY()
	UState* ChargeAttack;
	UPROPERTY()
	UState* TailSweep;
	UPROPERTY()
	UState* Laser;

	TArray<FAttackType> RangedAttackTypes;
	TArray<FAttackType> MeleeAttackTypes;
	TArray<FAttackType> BackAttackTypes;

	//Getter
	AMawOfSothrosPawn* GetSelfRef() const;
	APlayerCharacter* GetPlayer() const;

protected:
	virtual void BeginPlay() override;

private:
	//References
	UPROPERTY()
	AMawOfSothrosPawn* SelfRef;
	UPROPERTY()
	APlayerCharacter* Player;
};
