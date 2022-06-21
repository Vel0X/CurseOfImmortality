// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/FindStartLocation.h"

#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UFindStartLocation::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Running = true;
	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Find Location State Entered"))
	}
}

void UFindStartLocation::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Running = false;
	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Find Location State Exit"))
	}
}

void UFindStartLocation::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (Path.IsEmpty())
	{
		Controller->FindRandomPath(Path, RandomLocation);
	}
	else
	{
		if (Cast<ABaseEnemyPawn>(Controller->CheckLineOfSight(Player->GetActorLocation()).GetActor()))
		{
			if (PathfindingTimer <= 0)
			{
				Controller->FindRandomPath(Path, RandomLocation);
				PathIndex = 0;
				PathfindingTimer = 2.f;
			}
			else
			{
				if (!Path.IsEmpty())
				{
					if (Controller->FollowPath(Path, DeltaTime, PathIndex))
					{
						PathIndex++;
					}
				}
			}
		}
		else
		{
			if (Controller->FollowPath(Path, DeltaTime, PathIndex))
			{
				PathIndex++;
			}
		}

		PathfindingTimer -= DeltaTime;

		RandomLocation.Z = 0;
		FVector PlayerLocation = Player->GetActorLocation();
		FVector OwnLocation = SelfRef->GetActorLocation();
		PlayerLocation.Z = 0;
		OwnLocation.Z = 0;

		if (FVector::Dist(OwnLocation, PlayerLocation) < SelfRef->DistJumpAttack)
		{
			Controller->Transition(Controller->Running, Controller);
		}
		if (FVector::Dist(OwnLocation, RandomLocation) < 50.f)
		{
			Controller->Transition(Controller->Idle, Controller);
		}
	}
}
