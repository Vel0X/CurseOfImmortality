// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

#include "DeprivedPawn.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "States/DeprivedIdle.h"
#include "States/DeprivedRunning.h"

UDeprivedStateMachine::UDeprivedStateMachine()
{
}

void UDeprivedStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentState->OnStateUpdate(DeltaTime);
}

void UDeprivedStateMachine::BeginPlay()
{
	Super::BeginPlay();

	SelfRef = Cast<ADeprivedPawn>(GetOwner());
	Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	//Initialise States
	Idle = NewObject<UDeprivedIdle>();
	Running = NewObject<UDeprivedRunning>();

	CurrentState = Running;
	CurrentState->OnStateEnter(this);
}

void UDeprivedStateMachine::MoveToTarget(FVector Target, float Speed, float DeltaTime)
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	Target.Normalize();
	FVector MoveDir(SelfRef->GetActorLocation() + Target * DeltaTime * Speed);
	SelfRef->SetActorLocation(MoveDir, true);
}

void UDeprivedStateMachine::FocusOnPlayer()
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	if (!Player) { UE_LOG(LogTemp, Error, TEXT("No Player in Deprived StateMachine")); }
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	const FRotator LookAtRotation = FRotator(0.f, Target.Rotation().Yaw, 0.f);
	SelfRef->GetCollisionCapsule()->SetWorldRotation(LookAtRotation);
}

ADeprivedPawn* UDeprivedStateMachine::GetSelfRef() const
{
	return SelfRef;
}

ABaseCharacter* UDeprivedStateMachine::GetPlayer() const
{
	return Player;
}
