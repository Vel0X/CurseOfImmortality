// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterMovement.h"
#include "InputManager.generated.h"


class APlayerCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURSEOFIMMORTALITY_API UInputManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void MoveForward(float Value);

	void MoveRight(float Value);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInput(UInputComponent* InputComponent);
	
	APlayerCharacter *Player;

	UCharacterMovement *MovementComponent;

	FVector MoveInput;
	
};
