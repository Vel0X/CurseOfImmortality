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

	FVector HeadLocation = SelfRef->HeadLocation->GetComponentLocation();
	FVector MidLocation = SelfRef->GetActorLocation();
	FVector BackLocation = SelfRef->BackLocation->GetComponentLocation();
	FVector PlayerLocation = Player->GetActorLocation();
	HeadLocation.Z = 0;
	MidLocation.Z = 0;
	BackLocation.Z = 0;
	PlayerLocation.Z = 0;

	FVector Dir = PlayerLocation - HeadLocation;
	FVector Forward = SelfRef->GetActorForwardVector();
	Dir.Z = 0;
	Forward.Z = 0;

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
		if (FVector::Dist(PlayerLocation, HeadLocation) >= SelfRef->ChargeRange)
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
			if (Controller->CalculateAngleBetweenVectors(Dir, Forward) <= 40.f)
			{
				UE_LOG(LogTemp, Error, TEXT("NormalAttack: %f"), FVector::Dist(PlayerLocation, HeadLocation))
				if (FVector::Dist(PlayerLocation, HeadLocation) <= SelfRef->AttackRange)
				{
					Controller->Transition(Controller->NormalAttack, Controller);
				}
			}
			else if (Controller->CalculateAngleBetweenVectors(Dir, Forward) >= 160.f)
			{
				UE_LOG(LogTemp, Error, TEXT("Kick: %f"), FVector::Dist(PlayerLocation, BackLocation))
				if (FVector::Dist(PlayerLocation, BackLocation) <= SelfRef->AttackRange)
				{
					Controller->Transition(Controller->Kick, Controller);
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Stomping: %f"), FVector::Dist(PlayerLocation, MidLocation))
				if (FVector::Dist(PlayerLocation, MidLocation) <= SelfRef->AttackRange)
				{
					Controller->Transition(Controller->Stomping, Controller);
				}
			}
		}
		Controller->MoveToTarget(PlayerLocation, SelfRef->Stats[Movespeed], DeltaTime);
	}

	PathfindingTimer -= DeltaTime;
}
