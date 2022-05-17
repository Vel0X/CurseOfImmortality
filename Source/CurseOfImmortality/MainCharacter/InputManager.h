// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputManager.generated.h"

class UPlayerAnim;
class UCharacterMovement;

UENUM()
enum class InputAction
{
	NoAction 			UMETA(DisplayName = "Idle"),
	Running				UMETA(DisplayName = "Running"),
	MeleeAbility		UMETA(DisplayName = "MeleeAbility"),
	RangedAbility		UMETA(DisplayName = "RangedAbility"),
	SpecialAbility		UMETA(DisplayName = "SpecialAbility"),
	Dash				UMETA(DisplayName = "Dash"),
};

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

	void AddToBuffer(InputAction _InputAction);

	void DoAction(InputAction _InputAction);
	
	void MoveForward(float Value);

	void MoveRight(float Value);

	void MeleeAbility();

	void RangedAbility();

	void SpecialAbility();
	
	void Dash();

	TArray<InputAction> InputBuffer;
	
	UPROPERTY(EditAnywhere)
	float MaxBufferTime;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInput(UInputComponent* InputComponent);

	UPROPERTY(EditAnywhere)
	APlayerCharacter *Player;

	UPROPERTY(EditAnywhere)
	UCharacterMovement *MovementComponent;

	FVector MoveInput;

	InputAction LastAction;
};


