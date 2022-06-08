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
	Feast = NewObject<UDeprivedFeast>();
	FindStartLocation = NewObject<UFindStartLocation>();
}

void UDeprivedStateMachine::MoveToTarget(FVector Target, float Speed, float DeltaTime) const
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	Target = Target - SelfRef->GetActorLocation();
	Target.Z = 0.f;
	Target.Normalize();

	FVector MoveDir(SelfRef->GetActorLocation() + Target * DeltaTime * Speed);
	SelfRef->MovementComponent->SetDirection(Target, Speed);
}

void UDeprivedStateMachine::FocusOnLocation(FVector Location, float DeltaTime) const
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

	Target.Z = 0;
	const FRotator LookAtRotation(
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, 90.f).Rotation());
	SelfRef->CapsuleComponent->SetWorldRotation(LookAtRotation);
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
