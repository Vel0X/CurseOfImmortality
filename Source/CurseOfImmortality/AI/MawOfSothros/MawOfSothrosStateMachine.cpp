// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"

#include "MawOfSothrosPawn.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "States/MawOfSothrosChargeAttack.h"
#include "States/MawOfSothrosGroundSlam.h"
#include "States/MawOfSothrosIdle.h"
#include "States/MawOfSothrosTailSweep.h"
#include "States/MawOfSothrosVomit.h"

void UMawOfSothrosStateMachine::BeginPlay()
{
	Super::BeginPlay();

	//Initialise References
	SelfRef = Cast<AMawOfSothrosPawn>(GetOwner());

	//Initialise States
	Idle = NewObject<UMawOfSothrosIdle>();
	Vomit = NewObject<UMawOfSothrosVomit>();
	ChargeAttack = NewObject<UMawOfSothrosChargeAttack>();
	TailSweep = NewObject<UMawOfSothrosTailSweep>();
	GroundSlam = NewObject<UMawOfSothrosGroundSlam>();

	//Log States
	Idle->Verbose = true;
	Vomit->Verbose = true;
	ChargeAttack->Verbose = true;
	TailSweep->Verbose = true;
	GroundSlam->Verbose = true;
}

void UMawOfSothrosStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Player)
	{
		Player = FPersistentWorldManager::PlayerCharacter;
		CurrentState = Idle;
		CurrentState->OnStateEnter(this);
	}
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Maw StateMachine")); }
	if (!CurrentState) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Maw StateMachine")); }

	if (!SelfRef->Dead)
	{
		CurrentState->OnStateUpdate(DeltaTime);
	}
}

void UMawOfSothrosStateMachine::MoveToTarget(FVector Target, float Speed, float DeltaTime)
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Maw StateMachine")); }
	Target = Target - SelfRef->GetActorLocation();
	Target.Z = 0.f;
	Target.Normalize();

	// SelfRef->MovementComponent->SetDirection(Target, Speed);

	FVector MoveDir(SelfRef->GetActorLocation() + Target * DeltaTime * Speed);
	SelfRef->SetActorLocation(MoveDir, true);
}

void UMawOfSothrosStateMachine::FocusOnPlayer(float DeltaTime)
{
	if (!SelfRef)
	{
		UE_LOG(LogTemp, Error, TEXT("No Self Ref in Maw StateMachine"));
		return;
	}
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player in Maw StateMachine"));
		return;
	}
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();
	const FRotator LookAtRotation(
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, 45.f).Rotation());

	const FRotator ZeroedRotation = FRotator(0.f, LookAtRotation.Yaw, 0.f);

	SelfRef->CapsuleComponent->SetWorldRotation(ZeroedRotation);
}

AMawOfSothrosPawn* UMawOfSothrosStateMachine::GetSelfRef() const
{
	if (!SelfRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Self Ref in Deprived StateMachine"))
	}
	return SelfRef;
}

APlayerCharacter* UMawOfSothrosStateMachine::GetPlayer() const
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Self Ref in Deprived StateMachine"))
	}
	return Player;
}
