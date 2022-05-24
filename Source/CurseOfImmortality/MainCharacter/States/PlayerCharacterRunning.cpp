// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterRunning.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacterStateMachine.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"

void UPlayerCharacterRunning::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();

	SelfRef->Running = true;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Running State Entered"))
	}
}

void UPlayerCharacterRunning::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->Running = false;
	SelfRef->CurrentMovementSpeed = 0;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit Running State"))
	}
}

void UPlayerCharacterRunning::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	switch (*Controller->NewAction)
	{
	case InputAction::NoAction:
		Controller->Transition(Controller->Idle, Controller);
		break;
	case InputAction::MeleeAbility:
		Controller->Transition(Controller->MeleeAttack, Controller);
		break;
	case InputAction::RangedAbility:
		Controller->Transition(Controller->RangedAttack, Controller);
		break;
	case InputAction::SpecialAbility:
		Controller->Transition(Controller->SpecialAttack, Controller);
		break;
	case InputAction::Dash:
		if (SelfRef->CurrentDashCooldown <= 0)
		{
			Controller->Transition(Controller->Dash, Controller);
		}
		break;
	case InputAction::Running:
		break;
	default:
		//Controller->GetSelfRef()->InputManager->LastAction = InputAction::NoAction;
		//Controller->Transition(Controller->Idle, Controller);
		break;
	}
}
