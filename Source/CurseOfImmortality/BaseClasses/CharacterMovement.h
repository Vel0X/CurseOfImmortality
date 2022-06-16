// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMovement.generated.h"

class UActorComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURSEOFIMMORTALITY_API UCharacterMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	FRotator GoalRotation;
	float TimeToRotate;
	float CurrentTimeToRotate;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetDirection(FVector MoveInput, float MoveSpeed);

	void MoveWithCorrection(FVector DirectionToMove, float DeltaTime, float Speed) const;

	void SmoothRotation(FRotator Rotation, float Time);
	
	FVector Direction;
	bool DirectionSet;
	float CurrentSpeed;
	bool Rotating = false;
};
