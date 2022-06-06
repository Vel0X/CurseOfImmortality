// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRecover.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"

void UDeprivedRecover::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Recover = true;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Recover State Entered"))
	}
}

void UDeprivedRecover::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Recover = false;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit State Recover"))
	}

	SelfRef->CurrentRecoverDuration = SelfRef->RecoverDuration;
}

void UDeprivedRecover::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnLocation(Player->GetActorLocation(),DeltaTime);

	SelfRef->CurrentRecoverDuration -= DeltaTime;

	if (SelfRef->CurrentRecoverDuration <= 0)
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
