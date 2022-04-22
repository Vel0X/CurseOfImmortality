// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedHitPlayer.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedHitPlayer::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Controller->GetSelfRef()->SetHitPlayer(true);
	UE_LOG(LogTemp, Warning, TEXT("Hit Player State Entered"))
}

void UDeprivedHitPlayer::OnStateExit()
{
	Super::OnStateExit();

	Controller->GetSelfRef()->SetHitPlayer(false);
	UE_LOG(LogTemp, Warning, TEXT("Exit State Hit Player"))

	RemainingTime = Duration;
}

void UDeprivedHitPlayer::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnPlayer();

	RemainingTime -= DeltaTime * 1;

	if (RemainingTime <= 0)
	{
		Controller->Transition(Controller->GetRunning(), Controller);
	}
}
