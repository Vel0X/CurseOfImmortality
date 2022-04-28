// Fill out your copyright notice in the Description page of Project Settings.


#include "InputManager.h"

#include "PlayerCharacter.h"


// Sets default values for this component's properties
UInputManager::UInputManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Player = static_cast <APlayerCharacter*>(GetOwner());
	if(Player != nullptr)
	{
		MovementComponent = Player->MovementComponent;
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is Null"));
	}
}


// Called when the game starts
void UInputManager::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UInputManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Called to bind functionality to input
void UInputManager::SetupPlayerInput(UInputComponent* InputComponent)
{
	InputComponent->BindAxis("MoveForward", this, &UInputManager::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &UInputManager::MoveRight);
}

void UInputManager::MoveForward(float Value)
{
	MoveInput.X = Value;
	if(MovementComponent != nullptr)
	{
		MovementComponent->SetDirection(MoveInput, Player->MovementSpeed);
	}
	
}

void UInputManager::MoveRight(float Value)
{
	MoveInput.Y = Value;
	if(MovementComponent != nullptr)
	{
		MovementComponent->SetDirection(MoveInput, Player->MovementSpeed);
	}
	
}