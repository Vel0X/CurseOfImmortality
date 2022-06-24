// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterRanged.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"
#include "CurseOfImmortality/MainCharacter/PlayerAnim.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacterStateMachine.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"

void UPlayerCharacterRanged::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);
	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();
	SelfRef->PlayerAnim->SyncAnimAttackSpeed(SelfRef->Stats[AttackSpeed]);
	SelfRef->PlayerAnim->Ranged = true;
	SelfRef->CurrentAnimationDuration = SelfRef->PlayerAnim->RangedDuration1;

	Cast<APlayerCharacter>(SelfRef)->CurrentMovementSpeed = 0;

	if (FPersistentWorldManager::GetLogLevel(PlayerStateMachine))
		UE_LOG(LogTemp, Warning, TEXT("Ranged State Entered"))
	
}

void UPlayerCharacterRanged::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->InputManager->MoveLock = false;
	SelfRef->PlayerAnim->Ranged = false;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit Ranged State"))
	}
}

void UPlayerCharacterRanged::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
	
	if(Controller->GetSelfRef()->InputManager->LastAction == InputAction::Dash && SelfRef->CurrentDashCooldown <= 0)
	{
		Controller->Transition(Controller->Dash, Controller);
	}
	if(SelfRef->PlayerAnim->FireRanged)
	{
		SelfRef->AttackManager->OnKeyPressed(Ranged, SelfRef->SkeletalMesh->GetSocketLocation("LeftHandSocket"));
		SelfRef->PlayerAnim->FireRanged = false;
	}
	else if (SelfRef->CurrentAnimationDuration <= 0)
	{
		Controller->GetSelfRef()->InputManager->LastAction = InputAction::NoAction;
		Controller->Transition(Controller->Idle, Controller);
	}
}
