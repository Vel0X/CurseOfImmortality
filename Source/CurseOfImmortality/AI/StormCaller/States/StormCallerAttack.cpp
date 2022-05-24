// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/StormCaller/States/StormCallerAttack.h"

#include "CurseOfImmortality/AI/AIBaseClasses/RandomAOEAbilty.h"
#include "CurseOfImmortality/AI/StormCaller/StormCallerPawn.h"
#include "CurseOfImmortality/AI/StormCaller/StormCallerStateMachine.h"

void UStormCallerAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UStormCallerStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Attack = true;
	//UE_LOG(LogTemp, Warning, TEXT("Attack State Entered"))
}

void UStormCallerAttack::OnStateExit()
{
	Super::OnStateExit();
}

void UStormCallerAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (SelfRef->CurrentAttackCoolDown <= 0)
	{
		SelfRef->StormCast->StartAbility();
		SelfRef->CurrentAttackCoolDown = SelfRef->AttackCoolDown;
	}
}
