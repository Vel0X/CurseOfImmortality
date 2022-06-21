// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedFrenziedAttack.h"

#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"


void UDeprivedFrenziedAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();
	SelfRef->FrenziedAttack = true;
	SelfRef->AnimationEnd = false;

	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("FrenziedAttack State Entered"))
	}
}

void UDeprivedFrenziedAttack::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->FrenziedAttack = false;

	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit State FrenziedAttack"))
	}
}

void UDeprivedFrenziedAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnLocation(Player->GetActorLocation(), DeltaTime);

	const UAnimInstance* Animation = SelfRef->Mesh->GetAnimInstance();
	float CurveValue;
	Animation->GetCurveValue(FName("MovementSpeed"), CurveValue);

	const FVector PlayerLocation = Player->GetActorLocation();

	if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) > SelfRef->MinDistFrenziedAttack)
	{
		if (Controller->CheckLineOfSight(Player->GetActorLocation()).bBlockingHit)
		{
			if (PathfindingTimer <= 0)
			{
				Controller->FindPathToPlayer(Path);
				PathIndex = 0;
				PathfindingTimer = 0.5f;
			}
			if (!Path.IsEmpty())
			{
				if (Controller->FollowPath(Path, DeltaTime, PathIndex, 720.f))
				{
					PathIndex++;
				}
			}
			PathfindingTimer -= DeltaTime;
		}
		else
		{
			if (!Path.IsEmpty())
			{
				Path.Empty();
			}
			Controller->MoveToTarget(PlayerLocation, SelfRef->Stats[Movespeed] * CurveValue, DeltaTime);
		}
	}
	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Recover, Controller);
	}
}
