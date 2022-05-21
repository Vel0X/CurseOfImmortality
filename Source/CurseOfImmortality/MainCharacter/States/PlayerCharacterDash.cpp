// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterDash.h"

#include "CurseOfImmortality/MainCharacter/PlayerCharacterStateMachine.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"

void UPlayerCharacterDash::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UPlayerCharacterStateMachine>(StateMachine);
	SelfRef = Controller->GetSelfRef();
	
	SelfRef->Dash = true;
	SelfRef->CurrentAnimationDuration = SelfRef->DashDuration1;
	SelfRef->CurrentDashCooldown = SelfRef->DashCooldown;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dash State Entered"))
	}
}

void UPlayerCharacterDash::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->Dash = false;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit Dash State"))
	}
}

void UPlayerCharacterDash::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
	
	if (SelfRef->CurrentAnimationDuration <= 0)
	{
		SelfRef->InputManager->LastAction = InputAction::NoAction;
		Controller->Transition(Controller->Idle, Controller);
	}
	//SelfRef->GetRootComponent()->AddWorldOffset(SelfRef->GetActorForwardVector() * DeltaTime * SelfRef->DashSpeed, true);
	FHitResult* Result = new FHitResult();
	SelfRef->AddActorWorldOffset(SelfRef->GetActorForwardVector() * DeltaTime * SelfRef->DashSpeed,
									true, Result);
	if(Result != nullptr)
	{
		if (Result->GetActor()!= SelfRef && Result->GetActor()!= nullptr)
		{
			FVector UndesiredMotion = Result->ImpactNormal * (FVector::DotProduct(SelfRef->GetActorForwardVector(), Result->ImpactNormal));
				
			SelfRef->AddActorWorldOffset((SelfRef->GetActorForwardVector()-UndesiredMotion) * DeltaTime * SelfRef->DashSpeed,
									true);
		}
	}
}