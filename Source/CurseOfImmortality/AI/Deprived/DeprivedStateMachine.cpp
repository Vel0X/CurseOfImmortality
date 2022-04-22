// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

#include "DeprivedPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
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

ADeprivedPawn* UDeprivedStateMachine::GetSelfRef() const
{
	return SelfRef;
}

ABaseCharacter* UDeprivedStateMachine::GetPlayer() const
{
	return Player;
}

void UDeprivedStateMachine::BeginPlay()
{
	Super::BeginPlay();

	SelfRef = Cast<ADeprivedPawn>(GetOwner());
	Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	CurrentState = NewObject<UDeprivedRunning>(Running);
}

void UDeprivedStateMachine::MoveToTarget(FVector Target, float Speed, float DeltaTime)
{
	Target.Normalize();
	FVector MoveDir(SelfRef->GetActorLocation() + Target * DeltaTime * Speed);
	SelfRef->SetActorLocation(MoveDir, true);
}

void UDeprivedStateMachine::FocusOnPlayer()
{
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	const FRotator LookAtRotation = FRotator(0.f, Target.Rotation().Yaw, 0.f);
	SelfRef->GetCollisionCapsule()->SetWorldRotation(LookAtRotation);
}
