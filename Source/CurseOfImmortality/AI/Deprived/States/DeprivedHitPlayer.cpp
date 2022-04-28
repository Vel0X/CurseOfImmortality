// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedHitPlayer.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedHitPlayer::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->HitPlayer = true;
	UE_LOG(LogTemp, Warning, TEXT("Hit Player State Entered"))
}

void UDeprivedHitPlayer::OnStateExit()
{
	Super::OnStateExit();

	Controller->GetSelfRef()->HitPlayer = false;
	UE_LOG(LogTemp, Warning, TEXT("Exit State Hit Player"))


	SelfRef->CurrentRecoverDuration = SelfRef->RecoverDuration;
}

void UDeprivedHitPlayer::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnPlayer();

	SelfRef->CurrentRecoverDuration -= DeltaTime;

	if (SelfRef->CurrentRecoverDuration <= 0.f)
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
