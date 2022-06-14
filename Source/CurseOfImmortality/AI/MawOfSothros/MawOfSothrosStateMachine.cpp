// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"

#include "MawOfSothrosPawn.h"
#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "States/MawOfSothrosBaseState.h"
#include "States/MawOfSothrosChargeAttack.h"
#include "States/MawOfSothrosGroundSlam.h"
#include "States/MawOfSothrosStart.h"
#include "States/MawOfSothrosIdle.h"
#include "States/MawOfSothrosLaser.h"
#include "States/MawOfSothrosTailSweep.h"
#include "States/MawOfSothrosVomit.h"

UMawOfSothrosStateMachine::UMawOfSothrosStateMachine()
{
	// RangedAttackTypes.Add(FAttackType(VomitState, 100));
	// RangedAttackTypes.Add(FAttackType(ChargeAttackState, 100));
	RangedAttackTypes.Add(FAttackType(LaserState, 100));

	MeleeAttackTypes.Add(FAttackType(GroundSlamState, 100));
	MeleeAttackTypes.Add(FAttackType(ChargeAttackState, 50));
	MeleeAttackTypes.Add(FAttackType(VomitState, 25));

	BackAttackTypes.Add(FAttackType(TailSweepState, 100));;
}

void UMawOfSothrosStateMachine::BeginPlay()
{
	Super::BeginPlay();

	//Initialise References
	SelfRef = Cast<AMawOfSothrosPawn>(GetOwner());

	//Initialise States
	Start = NewObject<UMawOfSothrosStart>();
	Idle = NewObject<UMawOfSothrosIdle>();
	Vomit = NewObject<UMawOfSothrosVomit>();
	ChargeAttack = NewObject<UMawOfSothrosChargeAttack>();
	TailSweep = NewObject<UMawOfSothrosTailSweep>();
	GroundSlam = NewObject<UMawOfSothrosGroundSlam>();
	Laser = NewObject<UMawOfSothrosLaser>();
}

void UMawOfSothrosStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Player)
	{
		Player = FPersistentWorldManager::PlayerCharacter;
		CurrentState = Start;
		CurrentState->OnStateEnter(this);
	}
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Maw StateMachine")); }
	if (!CurrentState) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Maw StateMachine")); }

	if (!SelfRef->Dead)
	{
		CurrentState->OnStateUpdate(DeltaTime);
	}
}

void UMawOfSothrosStateMachine::Move(float Speed, float DeltaTime)
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Maw StateMachine")); }

	const FVector MoveDir(SelfRef->GetActorForwardVector());
	SelfRef->MovementComponent->SetDirection(MoveDir, Speed);
}

void UMawOfSothrosStateMachine::FocusOnPlayer(const float DeltaTime, const float Speed) const
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
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, Speed).Rotation());

	const FRotator ZeroedRotation = FRotator(0.f, LookAtRotation.Yaw, 0.f);

	SelfRef->SetActorRotation(ZeroedRotation);
}

float UMawOfSothrosStateMachine::CalculateAngleBetweenVectors(FVector VectorOne, FVector VectorTwo) const
{
	VectorOne.Normalize();
	VectorTwo.Normalize();

	const float DotProduct = FVector::DotProduct(VectorOne, VectorTwo);

	const float Angle = FMath::Acos(DotProduct);
	float AngleInDegree = FMath::RadiansToDegrees(Angle);

	return AngleInDegree;
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
