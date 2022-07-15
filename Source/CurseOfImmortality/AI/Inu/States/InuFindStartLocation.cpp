// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Inu/States/InuFindStartLocation.h"

#include "CurseOfImmortality/AI/Inu/InuPawn.h"
#include "CurseOfImmortality/AI/Inu/InuStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UInuFindStartLocation::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UInuStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Running = true;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Find Start Location State Entered"))
	}
}

void UInuFindStartLocation::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Running = false;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit Find Start Location State"))
	}
}

void UInuFindStartLocation::OnStateUpdate(float DeltaTime)
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
			if (Controller->CheckLineOfSight(Path[PathIndex]))
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
						if (Controller->FollowPath(Path, DeltaTime, PathIndex, 500.f))
						{
							PathIndex++;
						}
					}
				}
			}
			else
			{
				if (Controller->FollowPath(Path, DeltaTime, PathIndex, 500.f))
				{
					PathIndex++;
				}
			}

			PathfindingTimer -= DeltaTime;

			RandomLocation.Z = 0;
			PlayerLocation.Z = 0;
			OwnLocation.Z = 0;

			if (FVector::Dist(OwnLocation, PlayerLocation) < SelfRef->TriggerRange)
			{
				Controller->Transition(Controller->Running, Controller);
			}
			if (FVector::Dist(OwnLocation, RandomLocation) < 250.f)
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
	if (Cast<APlayerCharacter>(SelfRef->LastDamagingActor))
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
