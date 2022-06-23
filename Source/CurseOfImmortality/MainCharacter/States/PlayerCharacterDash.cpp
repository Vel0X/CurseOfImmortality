// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterDash.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"
#include "CurseOfImmortality/MainCharacter/PlayerAnim.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacterStateMachine.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/SpawnablesList.h"

void UPlayerCharacterDash::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();
	
	SelfRef->PlayerAnim->Dash = true;
	SelfRef->CurrentAnimationDuration = SelfRef->PlayerAnim->DashDuration1;
	SelfRef->CurrentDashCooldown = SelfRef->DashCooldown;
	if (FPersistentWorldManager::GetLogLevel(PlayerStateMachine))
		UE_LOG(LogTemp, Warning, TEXT("Dash State Entered"))

	UNiagaraSystem* Vfx = FPersistentWorldManager::ObjectFactory->Spawnables->DashVFX;

	if(NiagaraComp)
		NiagaraComp->DestroyComponent();
	
	NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(Vfx, SelfRef->LowerAttachmentPoint, NAME_None, FVector(0.f),
		FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
	
}

void UPlayerCharacterDash::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->PlayerAnim->Dash = false;
	if (FPersistentWorldManager::GetLogLevel(PlayerStateMachine))
		UE_LOG(LogTemp, Warning, TEXT("Exit Dash State"))

	NiagaraComp->Deactivate();
}

void UPlayerCharacterDash::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
	if (SelfRef->CurrentAnimationDuration <= 0)
	{
		SelfRef->InputManager->LastAction = InputAction::NoAction;
		Controller->Transition(Controller->Idle, Controller);
	}
	SelfRef->MovementComponent->MoveWithCorrection(SelfRef->GetActorForwardVector(), DeltaTime, SelfRef->DashSpeed, true);
}