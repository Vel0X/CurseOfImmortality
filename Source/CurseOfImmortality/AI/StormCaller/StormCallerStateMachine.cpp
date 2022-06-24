// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/StormCaller/StormCallerStateMachine.h"

#include "StormCallerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "States/StormCallerAttack.h"
#include "States/StormCallerIdle.h"
void UStormCallerStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Player)
	{
		Player = FPersistentWorldManager::PlayerCharacter;
		CurrentState = Idle;
		CurrentState->OnStateEnter(this);
	}
	if (!SelfRef->Dead)
	{
		CurrentState->OnStateUpdate(DeltaTime);
		SelfRef->CurrentAttackCoolDown -= DeltaTime;
	}
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

	//Initialise States
	Idle = NewObject<UStormCallerIdle>();
	Attack = NewObject<UStormCallerAttack>();
}

void UStormCallerStateMachine::FocusOnPlayer(float DeltaTime)
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in StormCaller StateMachine")); }
	if (!Player) { UE_LOG(LogTemp, Error, TEXT("No Player in StormCaller StateMachine")); }
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	const FRotator LookAtRotation(
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, 100.f).Rotation());
	SelfRef->SetActorRotation(LookAtRotation);
}
