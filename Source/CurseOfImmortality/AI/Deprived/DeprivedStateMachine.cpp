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
	FindStartLocation = NewObject<UFindStartLocation>();

	//Log States
	// Idle->Verbose = true;
	// Running->Verbose = true;
	// JumpAttack->Verbose = true;
	// HitPlayer->Verbose = true;
	// Recover->Verbose = true;
	// NormalAttack->Verbose = true;
	// FindStartLocation->Verbose = true;
}

void UDeprivedStateMachine::MoveToTarget(FVector Target, float Speed, float DeltaTime)
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	Target = Target - SelfRef->GetActorLocation();
	Target.Z = 0.f;
	Target.Normalize();

	// SelfRef->MovementComponent->SetDirection(Target, Speed);

	FVector MoveDir(SelfRef->GetActorLocation() + Target * DeltaTime * Speed);
	SelfRef->SetActorLocation(MoveDir, true);
}

void UDeprivedStateMachine::FocusOnPlayer()
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
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	const FRotator LookAtRotation = FRotator(0.f, Target.Rotation().Yaw, 0.f);
	SelfRef->CapsuleComponent->SetWorldRotation(LookAtRotation);
}

void UDeprivedStateMachine::FocusOnPath(FVector PathLocation, float DeltaTime)
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	const FVector SelfRefLocation(SelfRef->GetActorLocation());
	FVector Target = PathLocation - SelfRefLocation;

	Target.Z = 0;
	const FRotator LookAtRotation(
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, 270.f).Rotation());

	SelfRef->CapsuleComponent->SetWorldRotation(LookAtRotation);
}

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
