// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRecover.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedRecover::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();
	
	SelfRef->Recover = true;
	UE_LOG(LogTemp, Warning, TEXT("Recover State Entered"))
}

void UDeprivedRecover::OnStateExit()
{
	Super::OnStateExit();
	
	SelfRef->Recover = false;
	UE_LOG(LogTemp, Warning, TEXT("Exit State Recover"))

	SelfRef->CurrentRecoverDuration = SelfRef->RecoverDuration;
}

void UDeprivedRecover::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnPlayer();

	SelfRef->CurrentRecoverDuration -= DeltaTime;

	if (SelfRef->CurrentRecoverDuration <= 0)
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
