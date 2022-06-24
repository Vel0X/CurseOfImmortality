// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/StormCaller/States/StormCallerAttack.h"

#include "CurseOfImmortality/AI/AIBaseClasses/RandomAOEAbility.h"
#include "CurseOfImmortality/AI/StormCaller/StormCallerPawn.h"
#include "CurseOfImmortality/AI/StormCaller/StormCallerStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UStormCallerAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UStormCallerStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->CurrentAttackCoolDown = FMath::FRandRange(0.f, SelfRef->AttackCoolDown);

	SelfRef->Attack = true;

	if (FPersistentWorldManager::GetLogLevel(StormCallerStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack State Entered"))
	}
}

void UStormCallerAttack::OnStateExit()
{
	Super::OnStateExit();
}

void UStormCallerAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (WaitForAnimation)
	{
		if (SelfRef->CurrentAttackCoolDown <= 0.f)
		{
			SelfRef->StormCast->StartAbility(SelfRef->AbilitySpecification, SelfRef);
			SelfRef->CurrentAttackCoolDown = SelfRef->AttackCoolDown;
		}
	}
}
