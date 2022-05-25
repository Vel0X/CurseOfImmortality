// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterSpecial.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacterStateMachine.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UPlayerCharacterSpecial::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();
	
	SelfRef->Special = true;
	SelfRef->CurrentAnimationDuration = SelfRef->SpecialDuration1;
	
	Cast<APlayerCharacter>(SelfRef)->CurrentMovementSpeed = 0;

	if (FPersistentWorldManager::GetLogLevel(PlayerStateMachine))
		UE_LOG(LogTemp, Warning, TEXT("Special State Entered"))
	
}

void UPlayerCharacterSpecial::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->Special = false;
	if (FPersistentWorldManager::GetLogLevel(PlayerStateMachine))
		UE_LOG(LogTemp, Warning, TEXT("Exit Special State"))
	
}

void UPlayerCharacterSpecial::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
	
	if(Controller->GetSelfRef()->InputManager->LastAction == InputAction::Dash && SelfRef->CurrentDashCooldown <= 0)
	{
		Controller->Transition(Controller->Dash, Controller);
	}
	else if (SelfRef->CurrentAnimationDuration <= 0)
	{
		Controller->GetSelfRef()->InputManager->LastAction = InputAction::NoAction;
		Controller->Transition(Controller->Idle, Controller);
	}
}