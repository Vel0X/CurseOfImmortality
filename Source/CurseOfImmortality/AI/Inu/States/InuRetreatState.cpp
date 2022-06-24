// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Inu/States/InuRetreatState.h"

#include "CurseOfImmortality/AI/Inu/InuPawn.h"
#include "CurseOfImmortality/AI/Inu/InuStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UInuRetreatState::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UInuStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	RetreatLocation = FVector::ZeroVector;

	Duration = 2.f;

	SelfRef->Running = true;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Retreat State Entered"))
	}
}

void UInuRetreatState::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Running = false;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Retreat State Exit"))
	}
}

void UInuRetreatState::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (Duration >= 0)
	{
		if (RetreatLocation.IsZero())
		{
			FVector OwnLocation = SelfRef->GetActorLocation();
			OwnLocation.Z = 0.f;
			FVector PlayerLocation = Player->GetActorLocation();
			PlayerLocation.Z = 0.f;

			FVector DirectionVector = OwnLocation - PlayerLocation;
			DirectionVector.Normalize();

			RetreatLocation = DirectionVector * 1000.f + OwnLocation;

			DrawDebugLine(SelfRef->GetWorld(), OwnLocation, RetreatLocation,
			              FColor::Red, true
			);
		}
		else
		{
			if (FVector::Dist(RetreatLocation, SelfRef->GetActorLocation()) <= 50.f)
			{
				Controller->Transition(Controller->Idle, Controller);
			}
			else
			{
				Controller->MoveToTarget(RetreatLocation, SelfRef->Stats[Movespeed], DeltaTime, 720.f);
			}
		}
	}
	else
	{
		Controller->Transition(Controller->Idle, Controller);
	}

	Duration -= DeltaTime;
}
