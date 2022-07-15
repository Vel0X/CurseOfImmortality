// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Inu/States/InuIdleState.h"

#include "CurseOfImmortality/AI/Inu/InuPawn.h"
#include "CurseOfImmortality/AI/Inu/InuStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UInuIdleState::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UInuStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Idle = true;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Idle State Entered"))
	}
}

void UInuIdleState::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Idle = false;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit Idle State"))
	}
}

void UInuIdleState::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	const FVector PlayerLocation = Player->GetActorLocation();

	if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->TriggerRange)
	{
		Controller->Transition(Controller->Running, Controller);
	}
	if (Cast<APlayerCharacter>(SelfRef->LastDamagingActor))
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
