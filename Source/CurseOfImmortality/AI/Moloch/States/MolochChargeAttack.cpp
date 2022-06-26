// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/States/MolochChargeAttack.h"

#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"
#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMolochChargeAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);
	
	Controller = Cast<UMolochStateMachine>(StateMachine);
	
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();
	
	SelfRef->ChargedAttack = false;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("ChargedAttack State Entered"))
	}
}

void UMolochChargeAttack::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->ChargedAttack = false;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("ChargedAttack State Exit"))
	}
}

void UMolochChargeAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
}
