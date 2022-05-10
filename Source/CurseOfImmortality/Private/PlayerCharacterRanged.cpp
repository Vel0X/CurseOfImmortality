// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterRanged.h"

#include "PlayerCharacterStateMachine.h"
#include "PlayerCharacter.h"

void UPlayerCharacterRanged::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();
	SelfRef->Ranged = true;
	SelfRef->CurrentAnimationDuration = SelfRef->RangedDuration1;

	Cast<APlayerCharacter>(SelfRef)->CurrentMovementSpeed = 0;
	
	UE_LOG(LogTemp, Warning, TEXT("Ranged State Entered"))
}

void UPlayerCharacterRanged::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->Ranged = false;
	UE_LOG(LogTemp, Warning, TEXT("Exit Ranged State"))
}

void UPlayerCharacterRanged::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
	
	if(Controller->GetSelfRef()->InputManager->LastAction == InputAction::Dash)
	{
		Controller->Transition(Controller->Dash, Controller);
	}
	else if (SelfRef->CurrentAnimationDuration <= 0)
	{
		Controller->GetSelfRef()->InputManager->LastAction = InputAction::NoAction;
		Controller->Transition(Controller->Idle, Controller);
	}
}
