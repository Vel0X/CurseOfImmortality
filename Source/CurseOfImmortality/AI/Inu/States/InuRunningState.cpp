// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Inu/States/InuRunningState.h"

#include "CurseOfImmortality/AI/Inu/InuPawn.h"
#include "CurseOfImmortality/AI/Inu/InuStateMachine.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UInuRunningState::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UInuStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Running = true;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Idle State Entered"))
	}
}

void UInuRunningState::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Running = false;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Idle State Entered"))
	}
}

void UInuRunningState::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	const FVector PlayerLocation = Player->GetActorLocation();

	if (Controller->CheckLineOfSight(PlayerLocation))
	{
		if (PathfindingTimer <= 0)
		{
			Controller->FindPathToPlayer(Path);
			PathIndex = 0;
			PathfindingTimer = 0.5f;
		}
		if (!Path.IsEmpty())
		{
			if (Controller->FollowPath(Path, DeltaTime, PathIndex))
			{
				PathIndex++;
			}
		}
		PathfindingTimer -= DeltaTime;
	}
	else
	{
		if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->AttackRange)
		{
			Controller->Transition(Controller->RangedAttack, Controller);
		}
		else
		{
			Controller->MoveToTarget(PlayerLocation, SelfRef->Stats[Movespeed], DeltaTime);
		}
	}
}
