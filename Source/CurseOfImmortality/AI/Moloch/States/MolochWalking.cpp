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

	FVector OwnLocation = SelfRef->HeadLocation->GetComponentLocation();
	FVector PlayerLocation = Player->GetActorLocation();
	OwnLocation.Z = 0;
	PlayerLocation.Z = 0;

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
		if (FVector::Dist(PlayerLocation, OwnLocation) >= SelfRef->ChargeRange)
		{
			if (SelfRef->CurrentChargeAttackCoolDown <= 0.f)
			{
				Controller->Transition(Controller->PrepareCharge, Controller);
				SelfRef->CurrentChargeAttackCoolDown = SelfRef->ChargeAttackCoolDown;
			}
			else
			{
				Controller->MoveToTarget(PlayerLocation, SelfRef->Stats[Movespeed], DeltaTime);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Angle: %f"),
			       Controller->CalculateAngleBetweenVectors(OwnLocation, PlayerLocation))
			if (FVector::Dist(PlayerLocation, OwnLocation) <= SelfRef->AttackRange)
			{
				if (Controller->CalculateAngleBetweenVectors(OwnLocation, PlayerLocation) <= 40.f)
				{
					Controller->Transition(Controller->NormalAttack, Controller);
				}
				else if (Controller->CalculateAngleBetweenVectors(OwnLocation, PlayerLocation) >= 140.f)
				{
					Controller->Transition(Controller->Kick, Controller);
				}
				else
				{
					Controller->Transition(Controller->Stomping, Controller);
				}
			}
		}
		Controller->MoveToTarget(PlayerLocation, SelfRef->Stats[Movespeed], DeltaTime);
	}

	PathfindingTimer -= DeltaTime;
}
