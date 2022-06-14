// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "DeprivedPawn.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "States/DeprivedHitPlayer.h"
#include "States/DeprivedIdle.h"
#include "States/DeprivedJumpAttack.h"
#include "States/DeprivedNormalAttack.h"
#include "States/DeprivedRecover.h"
#include "States/DeprivedRunning.h"
#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"
#include "States/DeprivedFeast.h"
#include "States/DeprivedFrenziedAttack.h"
#include "States/FindStartLocation.h"

UDeprivedStateMachine::UDeprivedStateMachine()
{
}

void UDeprivedStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!Player)
	{
		Player = FPersistentWorldManager::PlayerCharacter;
		CurrentState = FindStartLocation;
		CurrentState->OnStateEnter(this);
	}
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	if (!CurrentState) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }

	if (!SelfRef->Dead)
	{
		if (Player->Dead)
		{
			if (!StateChanged)
			{
				StateChanged = true;
				Transition(Feast, this);
			}
		}
		else
		{
			LastLocation = Player->GetActorLocation();
		}
		CurrentState->OnStateUpdate(DeltaTime);
	}
	SelfRef->CurrentJumpAttackCoolDown -= DeltaTime;
	SelfRef->CurrentFrenziedAttackCoolDown -= DeltaTime;
}

void UDeprivedStateMachine::BeginPlay()
{
	Super::BeginPlay();

	//Initialise References
	SelfRef = Cast<ADeprivedPawn>(GetOwner());

	//Initialise States
	Idle = NewObject<UDeprivedIdle>();
	Running = NewObject<UDeprivedRunning>();
	JumpAttack = NewObject<UDeprivedJumpAttack>();
	HitPlayer = NewObject<UDeprivedHitPlayer>();
	Recover = NewObject<UDeprivedRecover>();
	NormalAttack = NewObject<UDeprivedNormalAttack>();
	FrenziedAttack = NewObject<UDeprivedFrenziedAttack>();
	Feast = NewObject<UDeprivedFeast>();
	FindStartLocation = NewObject<UFindStartLocation>();
}

void UDeprivedStateMachine::MoveToTarget(FVector Target, const float MovementSpeed, const float DeltaTime,
                                         const float RotationSpeed) const
{
	// Target = SelfRef->GetActorLocation() - Target;
	FocusOnLocation(Target, DeltaTime, RotationSpeed);
	Target = Target - SelfRef->GetActorLocation();
	Target.Z = 0;
	SelfRef->MovementComponent->SetDirection(Target, MovementSpeed);
}

void UDeprivedStateMachine::FocusOnLocation(const FVector Location, const float DeltaTime,
                                            const float RotationSpeed) const
{
	if (!SelfRef)
	{
		UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine"));
		return;
	}
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player in Deprived StateMachine"));
		return;
	}
	FVector Target = Location - SelfRef->GetActorLocation();
	const FRotator LookAtRotation(
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, RotationSpeed).Rotation());
	const FRotator ZeroedRotation = FRotator(0.f, LookAtRotation.Yaw, 0.f);
	SelfRef->SetActorRotation(ZeroedRotation);
}

// void UDeprivedStateMachine::FocusOnPath(FVector PathLocation, float DeltaTime) const
// {
// 	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
// 	const FVector SelfRefLocation(SelfRef->GetActorLocation());
// 	FVector Target = PathLocation - SelfRefLocation;
//
// 	Target.Z = 0;
// 	const FRotator LookAtRotation(
// 		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, 270.f).Rotation());
//
// 	SelfRef->CapsuleComponent->SetWorldRotation(LookAtRotation);
// }

//Getter and Setter
ADeprivedPawn* UDeprivedStateMachine::GetSelfRef() const
{
	if (!SelfRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Self Ref in Deprived StateMachine"))
	}
	return SelfRef;
}

APlayerCharacter* UDeprivedStateMachine::GetPlayer() const
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player in Deprived StateMachine"))
	}
	return Player;
}

float UDeprivedStateMachine::CalculateAngleBetweenVectors(FVector VectorOne, FVector VectorTwo) const
{
	VectorOne.Normalize();
	VectorTwo.Normalize();

	const float DotProduct = FVector::DotProduct(VectorOne, VectorTwo);

	const float Angle = FMath::Acos(DotProduct);
	float AngleInDegree = FMath::RadiansToDegrees(Angle);

	return AngleInDegree;
}
