// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/StormCaller/StormCallerStateMachine.h"

#include "StormCallerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "States/StormCallerAttack.h"
#include "States/StormCallerIdle.h"

UStormCallerStateMachine::UStormCallerStateMachine()
{
}

void UStormCallerStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentState->OnStateUpdate(DeltaTime);
	FocusOnPlayer();
	SelfRef->CurrentAttackCoolDown -= DeltaTime;
}

AStormCallerPawn* UStormCallerStateMachine::GetSelfRef() const
{
	return SelfRef;
}

ABaseCharacter* UStormCallerStateMachine::GetPlayer() const
{
	return Player;
}

void UStormCallerStateMachine::BeginPlay()
{
	Super::BeginPlay();

	//Initialise References
	SelfRef = Cast<AStormCallerPawn>(GetOwner());
	Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	//Initialise States
	Idle = NewObject<UStormCallerIdle>();
	Attack = NewObject<UStormCallerAttack>();

	CurrentState = Idle;
	CurrentState->OnStateEnter(this);
}

void UStormCallerStateMachine::FocusOnPlayer()
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in StormCaller StateMachine")); }
	if (!Player) { UE_LOG(LogTemp, Error, TEXT("No Player in StormCaller StateMachine")); }
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	const FRotator LookAtRotation = FRotator(0.f, Target.Rotation().Yaw, 0.f);
	SelfRef->GetCollisionCapsule()->SetWorldRotation(LookAtRotation);
}
