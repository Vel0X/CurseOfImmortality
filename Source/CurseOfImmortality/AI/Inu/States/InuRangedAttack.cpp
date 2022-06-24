// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Inu/States/InuRangedAttack.h"

#include "CurseOfImmortality/AI/Inu/InuPawn.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UInuRangedAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UInuStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->RangedAttack = true;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("RangedAttack State Entered"))
	}
}

void UInuRangedAttack::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->RangedAttack = false;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("RangedAttack State Exit"))
	}
}

void UInuRangedAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnPlayer(DeltaTime);

	if (Controller->CheckLineOfSight(Player->GetActorLocation()))
	{
		Controller->Transition(Controller->Running, Controller);
	}
	if (FVector::Dist(Player->GetActorLocation(), SelfRef->GetActorLocation()) > SelfRef->TriggerRange)
	{
		Controller->Transition(Controller->Running, Controller);
	}
	if (FVector::Dist(Player->GetActorLocation(), SelfRef->GetActorLocation()) < 200.f)
	{
		Controller->Transition(Controller->Retreat, Controller);
	}
}
