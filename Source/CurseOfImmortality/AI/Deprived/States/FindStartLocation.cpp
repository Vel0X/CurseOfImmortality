// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/FindStartLocation.h"

#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UFindStartLocation::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	MoveInLocation = SelfRef->GetActorLocation() + SelfRef->GetActorForwardVector() * 1000.f;

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

	FVector PlayerLocation = Player->GetActorLocation();
	FVector OwnLocation = SelfRef->GetActorLocation();

	if (MoveInLocationArrived)
	{
		if (Path.IsEmpty())
		{
			Controller->FindRandomPath(Path, RandomLocation);
		}
		else
		{
			if (Cast<ABaseEnemyPawn>(Controller->GetHitsInLine(Path[PathIndex])[0].GetActor()))
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
						if (Controller->FollowPath(Path, DeltaTime, PathIndex, 360.f, 1.f))
						{
							PathIndex++;
						}
					}
				}
			}
			else
			{
				if (Controller->FollowPath(Path, DeltaTime, PathIndex, 360.f, 1.f))
				{
					PathIndex++;
				}
			}

			PathfindingTimer -= DeltaTime;

			RandomLocation.Z = 0;
			PlayerLocation.Z = 0;
			OwnLocation.Z = 0;

			if (FVector::Dist(OwnLocation, PlayerLocation) < SelfRef->DistJumpAttack)
			{
				Controller->Transition(Controller->Running, Controller);
			}
			if (FVector::Dist(OwnLocation, RandomLocation) < 150.f)
			{
				Controller->Transition(Controller->Idle, Controller);
			}
		}
	}
	else
	{
		Controller->MoveToTarget(MoveInLocation, SelfRef->Stats[Movespeed], DeltaTime, 90.f, true);
		if (WalkInDuration <= 0.f || FVector::Dist(OwnLocation, MoveInLocation) < 150.f)
		{
			MoveInLocationArrived = true;
		}
		WalkInDuration -= DeltaTime;
	}
}
