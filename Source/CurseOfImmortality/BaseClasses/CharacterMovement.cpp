// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMovement.h"
#include "BaseCharacter.h"
#include "VectorTypes.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"


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
}


// Called every frame
void UCharacterMovement::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DirectionSet)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Text,%d"), Direction.Length());
		if (Direction.Length() < 0.3)
		{
			DirectionSet = false;
			return;
		}

		float SpeedDep = Direction.Length();
		if (SpeedDep > 1)
		{
			SpeedDep = 1;
		}
		Direction.Normalize();

		if (Cast<APlayerCharacter>(GetOwner()) != nullptr)
		{

			if (Cast<APlayerCharacter>(GetOwner())->Melee)
			{
				if (UKismetMathLibrary::Acos(FVector::DotProduct(GetOwner()->GetActorForwardVector(), Direction)) < 1.5)
				{
					Direction = GetOwner()->GetActorForwardVector();
				}
				else
				{
					return;
				}
			}
		}
		GetOwner()->SetActorRotation(Direction.Rotation());

		if (Cast<APlayerCharacter>(GetOwner()) != nullptr)
		{
			if (Cast<APlayerCharacter>(GetOwner())->InputManager->LastAction == InputAction::Running)
			{
				Cast<ABaseCharacter>(GetOwner())->CurrentMovementSpeed = Cast<ABaseCharacter>(GetOwner())->
					Stats[EStats::Movespeed] * SpeedDep;
			}
		}
		else
		{
			Cast<ABaseCharacter>(GetOwner())->CurrentMovementSpeed = Cast<ABaseCharacter>(GetOwner())->Stats[EStats::Movespeed] * SpeedDep;
		}
		
		MoveWithCorrection(Direction, DeltaTime, Cast<ABaseCharacter>(GetOwner())->CurrentMovementSpeed);
		
		DirectionSet = false;
	}
}


void UCharacterMovement::SetDirection(FVector MoveInput, float MovementSpeedInput)
{
	if (!(MoveInput.IsZero() && Direction.IsZero()))
	{
		MovementSpeed = MovementSpeedInput;
		Direction = MoveInput;
		DirectionSet = true;
	}
	else
	{
		if (Cast<APlayerCharacter>(GetOwner()) != nullptr)
		{
			if (Cast<APlayerCharacter>(GetOwner())->InputManager->LastAction == InputAction::Running)
			//TODO Maybe do better
			{
				Cast<ABaseCharacter>(GetOwner())->CurrentMovementSpeed = 0;
				Cast<APlayerCharacter>(GetOwner())->InputManager->LastAction = InputAction::NoAction;
			}
		}
	}
}

void UCharacterMovement::MoveWithCorrection(FVector DirectionToMove, float DeltaTime, float Speed)
{
	FHitResult* Result = new FHitResult();
	GetOwner()->AddActorWorldOffset(DirectionToMove * DeltaTime * Speed,
									true, Result);
	if(Result != nullptr)
	{
		if (Result->GetActor()!= GetOwner() && Result->GetActor()!= nullptr)
		{
			FVector UndesiredMotion = Result->ImpactNormal * (FVector::DotProduct(DirectionToMove, Result->ImpactNormal));
				
			GetOwner()->AddActorWorldOffset((DirectionToMove-UndesiredMotion) * DeltaTime * Speed,
									true);
		}
	}

	delete Result;
}

