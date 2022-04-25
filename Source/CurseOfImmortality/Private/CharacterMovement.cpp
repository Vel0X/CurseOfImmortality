// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMovement.h"

// Sets default values for this component's properties
UCharacterMovement::UCharacterMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterMovement::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	RootComponent = Owner->GetRootComponent();
	
}


// Called every frame
void UCharacterMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DirectionSet)
	{
		RootComponent->SetRelativeRotation(Direction.Rotation());
		RootComponent->AddWorldOffset(Direction * DeltaTime * MovementSpeed, false);
		DirectionSet = false;
	}
}


void UCharacterMovement::SetDirection(FVector MoveInput, float MovementSpeedInput)
{
	//UE_LOG(LogTemp, Warning, TEXT("Text,%s"), *Direction.ToString());
	if(!MoveInput.IsZero())
	{
		MovementSpeed = MovementSpeedInput;
		Direction = MoveInput;
		/*if(MoveInput.X != 0)
		{
			Direction.X = MoveInput.X;
		}

		if(MoveInput.Y != 0)
		{
			Direction.Y = MoveInput.Y;
		}*/
		DirectionSet = true;
	}
}
