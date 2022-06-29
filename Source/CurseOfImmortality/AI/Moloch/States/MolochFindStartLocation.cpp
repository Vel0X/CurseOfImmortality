// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/States/MolochFindStartLocation.h"

#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"
#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMolochFindStartLocation::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMolochStateMachine>(StateMachine);

	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Walking = true;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("FindStartLocation State Entered"))
	}
}

void UMolochFindStartLocation::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Walking = false;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("FindStartLocation State Exit"))
	}
}

void UMolochFindStartLocation::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

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
					if (Controller->FollowPath(Path, DeltaTime, PathIndex, 180.f))
					{
						PathIndex++;
					}
				}
			}
		}
		else
		{
			if (Controller->FollowPath(Path, DeltaTime, PathIndex, 180.f))
			{
				PathIndex++;
			}
		}

		PathfindingTimer -= DeltaTime;

		RandomLocation.Z = 0;
		FVector PlayerLocation = Player->GetActorLocation();
		FVector OwnLocation = SelfRef->HeadLocation->GetComponentLocation();
		PlayerLocation.Z = 0;
		OwnLocation.Z = 0;

		if (FVector::Dist(OwnLocation, PlayerLocation) < SelfRef->TriggerRange)
		{
			SelfRef->CurrentChargeAttackCoolDown = FMath::FRandRange(0.f, SelfRef->ChargeAttackCoolDown);
			Controller->Transition(Controller->Walking, Controller);
		}
		if (FVector::Dist(OwnLocation, RandomLocation) < 150.f)
		{
			Controller->Transition(Controller->Idle, Controller);
		}
	}
}
