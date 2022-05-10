// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterDash.h"

#include "PlayerCharacterStateMachine.h"
#include "PlayerCharacter.h"

void UPlayerCharacterDash::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();
	
	SelfRef->Dash = true;
	SelfRef->CurrentAnimationDuration = SelfRef->DashDuration1;
	UE_LOG(LogTemp, Warning, TEXT("Dash State Entered"))
}

void UPlayerCharacterDash::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->Dash = false;
	UE_LOG(LogTemp, Warning, TEXT("Exit Dash State"))
}

void UPlayerCharacterDash::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
	
	if (SelfRef->CurrentAnimationDuration <= 0)
	{
		SelfRef->InputManager->LastAction = InputAction::NoAction;
		Controller->Transition(Controller->Idle, Controller);
	}
	SelfRef->GetRootComponent()->AddWorldOffset(SelfRef->GetActorForwardVector() * DeltaTime * 1500, true);
}