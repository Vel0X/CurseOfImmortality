// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRecover.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedRecover::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Controller->GetSelfRef()->SetRecover(true);
	UE_LOG(LogTemp, Warning, TEXT("Recover State Entered"))
}

void UDeprivedRecover::OnStateExit()
{
	Super::OnStateExit();

	Controller->GetSelfRef()->SetRecover(false);
	UE_LOG(LogTemp, Warning, TEXT("Exit State Recover"))

	RemainingTime = Duration;
}

void UDeprivedRecover::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnPlayer();

	RemainingTime -= DeltaTime * 1;

	if (RemainingTime <= 0)
	{
		Controller->Transition(Controller->GetRunning(), Controller);
	}
}
