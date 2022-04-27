// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedIdle.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedIdle::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Controller->GetSelfRef()->Idle = true;
	UE_LOG(LogTemp, Warning, TEXT("Idle State Entered"))
}

void UDeprivedIdle::OnStateExit()
{
	Super::OnStateExit();
	Controller->GetSelfRef()->Idle = false;
	UE_LOG(LogTemp, Warning, TEXT("Exit Idle State"))
}

void UDeprivedIdle::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("Refrence Controller Missing in Idle State"));
		return;
	}

	Controller->FocusOnPlayer();
	const FVector PlayerLocation = Controller->GetPlayer()->GetActorLocation();

	if (FVector::Dist(PlayerLocation, Controller->GetSelfRef()->GetActorLocation()) < Controller->GetSelfRef()->DistRunning)
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
