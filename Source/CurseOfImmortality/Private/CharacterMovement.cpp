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
	RootComponent = GetOwner()->GetRootComponent();
}


// Called every frame
void UCharacterMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DirectionSet)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Text,%d"), Direction.Length());
		if(Direction.Length() < 0.65)
		{
			DirectionSet = false;
			return;
		}
		Direction.Normalize();
		RootComponent->SetWorldRotation(Direction.Rotation());
		RootComponent->AddWorldOffset(Direction * DeltaTime * MovementSpeed, false);
		DirectionSet = false;
	}
}


void UCharacterMovement::SetDirection(FVector MoveInput, float MovementSpeedInput)
{
	if(!(MoveInput.IsZero() && Direction.IsZero()))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Text,%s"), *MoveInput.ToString());
		MovementSpeed = MovementSpeedInput;
		Direction = MoveInput;
		DirectionSet = true;
	}
}
