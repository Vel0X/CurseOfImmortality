// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/States/MolochIdle.h"

#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"
#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMolochIdle::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMolochStateMachine>(StateMachine);

	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Idle = true;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Idle State Entered"))
	}
}

void UMolochIdle::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Idle = false;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Idle State Exit"))
	}
}

void UMolochIdle::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (FVector::Dist(SelfRef->HeadLocation->GetComponentLocation(), Player->GetActorLocation()) <= SelfRef->
		TriggerRange)
	{
		SelfRef->CurrentChargeAttackCoolDown = FMath::FRandRange(0.f, SelfRef->ChargeAttackCoolDown);
		Controller->Transition(Controller->Walking, Controller);
	}
	if (Cast<APlayerCharacter>(SelfRef->LastDamagingActor))
	{
		Controller->Transition(Controller->Walking, Controller);
	}
}
