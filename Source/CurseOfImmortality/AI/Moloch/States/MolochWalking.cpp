// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/States/MolochWalking.h"

#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"
#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMolochWalking::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMolochStateMachine>(StateMachine);

	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Walking = true;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Walking State Entered"))
	}
}

void UMolochWalking::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Walking = false;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Walking State Exit"))
	}
}

void UMolochWalking::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	const FVector PlayerLocation = Player->GetActorLocation();

	if (Controller->CheckLineOfSight(PlayerLocation))
	{
		if (PathfindingTimer <= 0.f)
		{
			Path.Empty();
			Controller->FindPathToPlayer(Path);
			PathfindingTimer = 0.5f;
			PathIndex = 0;
		}
		else
		{
			if (!Path.IsEmpty())
			{
				if (Controller->FollowPath(Path, DeltaTime, PathIndex))
				{
					PathIndex++;
				};
			}
		}
	}
	else
	{
		Controller->MoveToTarget(PlayerLocation, SelfRef->Stats[Movespeed], DeltaTime);
	}
	
	PathfindingTimer -= DeltaTime;
}
