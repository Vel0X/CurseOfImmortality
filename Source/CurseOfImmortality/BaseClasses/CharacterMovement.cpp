// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMovement.h"
#include "BaseCharacter.h"
#include "VectorTypes.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"
#include "CurseOfImmortality/MainCharacter/PlayerAnim.h"


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

	if(Rotating)
	{
		FRotator NextRotator = FMath::RInterpTo(GetOwner()->GetActorRotation(), GoalRotation,DeltaTime,23);
		CurrentTimeToRotate -= DeltaTime;
		GetOwner()->SetActorRotation(NextRotator);
		if (CurrentTimeToRotate <= 0)
		{
			Rotating = false;
		}
	}
	
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
		//UE_LOG(LogTemp, Warning, TEXT("Text,%s"), *Direction.Rotation().ToString());

		if (Cast<APlayerCharacter>(GetOwner()) != nullptr)
		{

			if (Cast<APlayerCharacter>(GetOwner())->PlayerAnim->Melee)
			{
				if (UKismetMathLibrary::Acos(FVector::DotProduct(GetOwner()->GetActorForwardVector(), Direction)) < 1.5)
				{
					GetOwner()->SetActorRotation(Direction.Rotation());
					Direction = GetOwner()->GetActorForwardVector();
				}
				else
				{
					return;
				}
			}
		}
		SmoothRotation(Direction.Rotation(),0.15);

		if (Cast<APlayerCharacter>(GetOwner()) != nullptr)
		{
			if (Cast<APlayerCharacter>(GetOwner())->InputManager->LastAction == InputAction::Running)
			{
				Cast<ABaseCharacter>(GetOwner())->CurrentMovementSpeed = CurrentSpeed * SpeedDep;
			}
		}
		else
		{
			Cast<ABaseCharacter>(GetOwner())->CurrentMovementSpeed = CurrentSpeed * SpeedDep;
		}
		
		MoveWithCorrection(Direction, DeltaTime, CurrentSpeed);
		
		DirectionSet = false;
	}
}


void UCharacterMovement::SetDirection(FVector MoveInput, float MoveSpeed)
{
	if (!(MoveInput.IsZero() && Direction.IsZero()))
	{
		Direction = MoveInput;
		CurrentSpeed = MoveSpeed;
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

void UCharacterMovement::SmoothRotation(FRotator Rotation, float Time)
{
	Rotating = true;
	GoalRotation = Rotation;
	TimeToRotate = Time;
	CurrentTimeToRotate = Time;
}

