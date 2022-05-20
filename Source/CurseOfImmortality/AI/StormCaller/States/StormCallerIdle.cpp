// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/StormCaller/States/StormCallerIdle.h"
#include "CurseOfImmortality/AI/StormCaller/StormCallerPawn.h"
#include "CurseOfImmortality/AI/StormCaller/StormCallerStateMachine.h"

void UStormCallerIdle::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UStormCallerStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Idle = true;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Idle State Entered"))
	}
}

void UStormCallerIdle::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->Idle = false;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit Idle State"))
	}
}

void UStormCallerIdle::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	const FVector PlayerLocation = Player->GetActorLocation();

	if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->AwakeRange)
	{
		Controller->Transition(Controller->Attack, Controller);
	}
}
