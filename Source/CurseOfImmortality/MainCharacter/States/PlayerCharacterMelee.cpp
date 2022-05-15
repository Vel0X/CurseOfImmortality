// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterMelee.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacterStateMachine.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"

void UPlayerCharacterMelee::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();
	
	

	switch(SelfRef->MeleeComboCount)
	{
	case 0:
		{
			SelfRef->CurrentAnimationDuration = SelfRef->MeleeDuration1;
			SelfRef->MeleeComboCount += 1;
			SelfRef->MeleeStartFrame = 0;
		}
	case 1:
		{
			SelfRef->CurrentAnimationDuration = SelfRef->MeleeDuration2;
			SelfRef->MeleeComboCount += 1;
			SelfRef->MeleeStartFrame = 2.4 - (SelfRef->MeleeDuration3+SelfRef->MeleeDuration2);
		}
	case 2:
		{
			SelfRef->CurrentAnimationDuration = SelfRef->MeleeDuration3;
			SelfRef->MeleeComboCount = 0;
			SelfRef->MeleeStartFrame = 2.4 - (SelfRef->MeleeDuration3);
		}
	default:
		{
			SelfRef->CurrentAnimationDuration = SelfRef->MeleeDuration1;
			SelfRef->MeleeComboCount += 1;
			SelfRef->MeleeStartFrame = 0;
		}
	}
	
	SelfRef->Melee = true;
	SelfRef->CurrentMeleeFollowUpTime = SelfRef->MeleeFollowUpTime;
	
	Cast<APlayerCharacter>(SelfRef)->CurrentMovementSpeed = Cast<APlayerCharacter>(SelfRef)->MovementSpeedWhileAttacking;
	
	UE_LOG(LogTemp, Warning, TEXT("Melee State Entered"));
}

void UPlayerCharacterMelee::OnStateExit()
{
	Super::OnStateExit();
	Cast<APlayerCharacter>(SelfRef)->CurrentMovementSpeed = 0;
	UCapsuleComponent* HitBox = Cast<UCapsuleComponent>(SelfRef->GetDefaultSubobjectByName(TEXT("SwordHitbox"))); //TODO NEED TO FIND BETTER SOLUTION
	HitBox->SetGenerateOverlapEvents(false);
	SelfRef->Melee = false;
	UE_LOG(LogTemp, Warning, TEXT("Exit Melee State"))
}

void UPlayerCharacterMelee::OnStateUpdate(float DeltaTime)
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
