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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetDirection(FVector MoveInput, float MovementSpeedInput);

	void MoveWithCorrection(FVector DirectionToMove, float DeltaTime, float Speed);
	
	float MovementSpeed;
	
	FVector Direction;
	bool DirectionSet;

	UPROPERTY(EditAnywhere)
	USceneComponent* RootComponent;
	
};
