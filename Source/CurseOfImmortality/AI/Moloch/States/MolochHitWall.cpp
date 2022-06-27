// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/States/MolochHitWall.h"

#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"
#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMolochHitWall::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMolochStateMachine>(StateMachine);
	
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->AnimationEnd = false;
	
	SelfRef->HitWall = true;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitWall State Entered"))
	}
}

void UMolochHitWall::OnStateExit()
{
	Super::OnStateExit();
	
	SelfRef->HitWall = false;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitWall State Exit"))
	}
}

void UMolochHitWall::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Walking, Controller);
	}
}
