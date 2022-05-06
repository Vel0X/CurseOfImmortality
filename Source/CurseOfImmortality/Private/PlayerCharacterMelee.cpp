// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterMelee.h"

#include "PlayerCharacterStateMachine.h"
#include "PlayerCharacter.h"

void UPlayerCharacterMelee::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();
	
	SelfRef->Melee = true;
	SelfRef->CurrentAnimationDuration = SelfRef->MeleeDuration1;

	Cast<APlayerCharacter>(SelfRef)->CurrentMovementSpeed = Cast<APlayerCharacter>(SelfRef)->MovementSpeedWhileAttacking;
	
	UE_LOG(LogTemp, Warning, TEXT("Melee State Entered"));
}

void UPlayerCharacterMelee::OnStateExit()
{
	Super::OnStateExit();
	Cast<APlayerCharacter>(SelfRef)->CurrentMovementSpeed = 0;
	SelfRef->Melee = false;
	UE_LOG(LogTemp, Warning, TEXT("Exit Melee State"))
}

void UPlayerCharacterMelee::OnStateUpdate(float DeltaTime)
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
