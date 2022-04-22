// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

#include "DeprivedPawn.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "States/DeprivedHitPlayer.h"
#include "States/DeprivedIdle.h"
#include "States/DeprivedJumpAttack.h"
#include "States/DeprivedRecover.h"
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

	//Initialise References
	SelfRef = Cast<ADeprivedPawn>(GetOwner());
	Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	//Initialise States
	Idle = NewObject<UDeprivedIdle>();
	Running = NewObject<UDeprivedRunning>();
	JumpAttack = NewObject<UDeprivedJumpAttack>();
	HitPlayer = NewObject<UDeprivedHitPlayer>();
	Recover = NewObject<UDeprivedRecover>();
	
	CurrentState = Idle;
	CurrentState->OnStateEnter(this);
}

void UDeprivedStateMachine::MoveToTarget(FVector Target, float Speed, float DeltaTime)
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	Target.Normalize();
	const FVector MoveDir(SelfRef->GetActorLocation() + Target * DeltaTime * Speed);
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

//Getter and Setter
ADeprivedPawn* UDeprivedStateMachine::GetSelfRef() const
{
	return SelfRef;
}

ABaseCharacter* UDeprivedStateMachine::GetPlayer() const
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player in Deprived StateMachine"))
	}
	return Player;
}

UState* UDeprivedStateMachine::GetIdle() const
{
	return Idle;
}

UState* UDeprivedStateMachine::GetRunning() const
{
	return Running;
}

UState* UDeprivedStateMachine::GetJumpAttack() const
{
	return JumpAttack;
}

UState* UDeprivedStateMachine::GetRecover() const
{
	return Recover;
}

UState* UDeprivedStateMachine::GetHitPlayer() const
{
	return HitPlayer;
}