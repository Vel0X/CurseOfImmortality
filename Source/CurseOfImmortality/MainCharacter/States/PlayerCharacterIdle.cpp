// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterIdle.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"
#include "CurseOfImmortality/MainCharacter/PlayerAnim.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacterStateMachine.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UPlayerCharacterIdle::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();
	
	SelfRef->PlayerAnim->Idle = true;
	if (FPersistentWorldManager::GetLogLevel(PlayerStateMachine))
		UE_LOG(LogTemp, Warning, TEXT("Idle State Entered"))
}

void UPlayerCharacterIdle::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->PlayerAnim->Idle = false;
	if (FPersistentWorldManager::GetLogLevel(PlayerStateMachine))
		UE_LOG(LogTemp, Warning, TEXT("Exit Idle State"))
	
}

void UPlayerCharacterIdle::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
	
	switch(*Controller->NewAction)
	{
		case InputAction::Running:
			Controller->Transition(Controller->Running, Controller);
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
		default:
			break;
	}
}
