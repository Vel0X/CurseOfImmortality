// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosVomit.h"

#include "NiagaraComponent.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"

void UMawOfSothrosVomit::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMawOfSothrosStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Vomit = true;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Vomit State Entered"))
	}
}

void UMawOfSothrosVomit::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Vomit = false;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Vomit State Exit"))
	}
}

void UMawOfSothrosVomit::ActivateVomit()
{
	SelfRef->VomitLowerJaw->Activate();
	SelfRef->VomitUpperJaw->Activate();
}

void UMawOfSothrosVomit::DeactivateVomit()
{
	SelfRef->VomitLowerJaw->Deactivate();
	SelfRef->VomitUpperJaw->Deactivate();
}

void UMawOfSothrosVomit::TransitionToIdle()
{
	Controller->Transition(Controller->Idle, Controller);
}
