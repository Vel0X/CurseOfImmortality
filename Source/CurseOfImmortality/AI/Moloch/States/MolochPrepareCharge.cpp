// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/States/MolochPrepareCharge.h"

#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"
#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMolochPrepareCharge::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMolochStateMachine>(StateMachine);

	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->AnimationEnd = false;

	SelfRef->PrepareCharge = true;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("PrepareCharge State Entered"))
	}
}

void UMolochPrepareCharge::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->PrepareCharge = false;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("PrepareCharge State Exit"))
	}
}

void UMolochPrepareCharge::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnLocation(Player->GetActorLocation(), DeltaTime, 90.f);

	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->ChargeAttack, Controller);
	}
}
