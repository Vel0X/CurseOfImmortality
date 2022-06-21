// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRunning.h"

#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UDeprivedRunning::OnStateEnter(UStateMachine* StateMachine)
{
	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Running = true;
	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Running State Entered"))
	}
}

void UDeprivedRunning::OnStateExit()
{
	SelfRef->Running = false;
	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Running State Exit"))
	}
}

void UDeprivedRunning::OnStateUpdate(float DeltaTime)
{
	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("Refrence Missing in State Running"));
		return;
	}

	const FVector PlayerLocation = Player->GetActorLocation();

	if (Controller->CheckLineOfSight(PlayerLocation).bBlockingHit)
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
		Controller->MoveToTarget(PlayerLocation, SelfRef->Stats[Movespeed], DeltaTime);
		if (!SelfRef->WeakDeprived)
		{
			if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistFrenziedAttack)
			{
				if (SelfRef->CurrentFrenziedAttackCoolDown <= 0.f)
				{
					SelfRef->CurrentFrenziedAttackCoolDown = SelfRef->FrenziedAttackCoolDown;
					Controller->Transition(Controller->FrenziedAttack, Controller);
					NoAttackChosen = false;
				}
			}
			else if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistJumpAttack)
			{
				if (SelfRef->CurrentJumpAttackCoolDown <= 0.f)
				{
					SelfRef->CurrentJumpAttackCoolDown = SelfRef->JumpAttackCoolDown;
					Controller->Transition(Controller->JumpAttack, Controller);
					NoAttackChosen = false;
				}
			}
		}
		if (NoAttackChosen)
		{
			if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistNormalAttack)
			{
				Controller->Transition(Controller->NormalAttack, Controller);
			}
		}
	}
	PathfindingTimer -= DeltaTime;
	NoAttackChosen = true;
}

void UDeprivedRunning::FollowPath(float DeltaTime)
{
}
