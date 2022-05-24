// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterDash.h"

#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"
#include "CurseOfImmortality/MainCharacter/PlayerAnim.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacterStateMachine.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UPlayerCharacterDash::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();
	
	SelfRef->Dash = true;
	SelfRef->CurrentAnimationDuration = SelfRef->DashDuration1;
	SelfRef->CurrentDashCooldown = SelfRef->DashCooldown;
	if (FPersistentWorldManager::GetLogLevel(PlayerStateMachine))
		UE_LOG(LogTemp, Warning, TEXT("Dash State Entered"))
	
}

void UPlayerCharacterDash::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->Dash = false;
	if (FPersistentWorldManager::GetLogLevel(PlayerStateMachine))
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
	SelfRef->MovementComponent->MoveWithCorrection(SelfRef->GetActorForwardVector(), DeltaTime, SelfRef->DashSpeed);
}