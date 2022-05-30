// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosTailSweep.h"

#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMawOfSothrosTailSweep::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);
	
	Controller = Cast<UMawOfSothrosStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->TailSweep = true;
	SelfRef->AnimationEnd = false;

	SelfRef->TailDamageSphere->SetGenerateOverlapEvents(true);

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tail Sweep State Entered"));
	}
}

void UMawOfSothrosTailSweep::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->TailSweep = false;

	SelfRef->TailDamageSphere->SetGenerateOverlapEvents(false);

	SelfRef->CurrentAttackCooldown = SelfRef->AttackCooldown;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tail Sweep State Exit"));
	}
}

void UMawOfSothrosTailSweep::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Idle, Controller);
	}
}
