// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMovement.h"
#include "BaseCharacter.h"
#include "VectorTypes.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
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


	if (Rotating)
	{
		FRotator NextRotator = FMath::RInterpTo(GetOwner()->GetActorRotation(), GoalRotation, DeltaTime, 23);
		CurrentTimeToRotate -= DeltaTime;
		if (!Cast<ABaseEnemyPawn>(GetOwner()))
		{
			GetOwner()->SetActorRotation(NextRotator);
		}
		if (CurrentTimeToRotate <= 0)
		{
			Rotating = false;
		}
	}

	if (DirectionSet)
	{
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

		SmoothRotation(Direction.Rotation(), 0.15);

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

		if (!MoveWithoutCorrection)
		{
			MoveWithCorrection(Direction, DeltaTime, Cast<ABaseCharacter>(GetOwner())->CurrentMovementSpeed, MoveThroughCharacters);
		} else
		{
			Direction.Z = 0;
			GetOwner()->AddActorWorldOffset(Direction * DeltaTime * Cast<ABaseCharacter>(GetOwner())->CurrentMovementSpeed, false);
		}
		DirectionSet = false;
	}
}


void UCharacterMovement::SetDirection(FVector MoveInput, float MoveSpeed, bool IgnoreAllCol, bool IgnoreCharacters)
{

	Direction = MoveInput;
	CurrentSpeed = MoveSpeed;
	DirectionSet = true;
	MoveWithoutCorrection = IgnoreAllCol;
	MoveThroughCharacters = IgnoreCharacters;
}

void UCharacterMovement::MoveWithCorrection(FVector DirectionToMove, const float DeltaTime, const float Speed, const bool IgnoreCharacters ) const
{
	//Reset Z to 0 for safety
	DirectionToMove.Z = 0;
	DirectionToMove.Normalize();
	
	FHitResult Result = FHitResult();
	AActor* Owner = GetOwner();
	const auto CapsuleCol = Cast<ABaseCharacter>(Owner)->CapsuleCollision;
	const auto CapsuleLocBeforeMove = CapsuleCol->GetComponentLocation();
	CapsuleCol->AddWorldOffset(DirectionToMove * DeltaTime * Speed, true, &Result);
	CapsuleCol->SetWorldLocation(CapsuleLocBeforeMove);

	if (IgnoreCharacters)
	 {
	 	if (Cast<ABaseCharacter>(Result.GetActor()) != nullptr)
	 	{
	 		Owner->AddActorWorldOffset(DirectionToMove * DeltaTime * Speed, false);
	 		return;
	 	}
	 }
	
	if (Result.GetActor() != Owner && Result.GetActor())
	{
		FVector CorrectedImpactNormal = Result.ImpactNormal;
		CorrectedImpactNormal.Z = 0;
		CorrectedImpactNormal.Normalize();
		const FVector UndesiredMotion = CorrectedImpactNormal * FVector::DotProduct(DirectionToMove, CorrectedImpactNormal);

		CapsuleCol->AddWorldOffset((DirectionToMove - UndesiredMotion) * DeltaTime * Speed, true, &Result);
		CapsuleCol->SetWorldLocation(CapsuleLocBeforeMove);

		if (Result.GetActor() != Owner && Result.GetActor())
		{
			CorrectedImpactNormal = Result.ImpactNormal;
			CorrectedImpactNormal.Z = 0;
			CorrectedImpactNormal.Normalize();
			
			const FVector UndesiredMotion2 = CorrectedImpactNormal * FVector::DotProduct(DirectionToMove - UndesiredMotion, CorrectedImpactNormal);
			Owner->AddActorWorldOffset(
				(DirectionToMove - UndesiredMotion - UndesiredMotion2) * DeltaTime * Speed, false);
		}
		else
		{
			Owner->AddActorWorldOffset((DirectionToMove - UndesiredMotion) * DeltaTime * Speed, false);
		}
	}
	else
	{
		Owner->AddActorWorldOffset(DirectionToMove * DeltaTime * Speed, false);
	}
}

void UCharacterMovement::SmoothRotation(FRotator Rotation, float Time)
{
	Rotating = true;
	GoalRotation = Rotation;
	TimeToRotate = Time;
	CurrentTimeToRotate = Time;
}
