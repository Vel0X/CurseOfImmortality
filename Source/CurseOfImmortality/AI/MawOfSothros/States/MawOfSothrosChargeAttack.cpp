// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosChargeAttack.h"

#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMawOfSothrosChargeAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMawOfSothrosStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->AnimationEnd = false;

	SelfRef->ChargeAttack = true;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Idle State Entered"))
	}
}

void UMawOfSothrosChargeAttack::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->CurrentAttackCooldown = SelfRef->AttackCooldown;

	SelfRef->ChargeAttack = false;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Exit Idle State"))
	}
}

void UMawOfSothrosChargeAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Idle, Controller);
	}
	
	const FVector PlayerLocation(Controller->GetPlayer()->GetActorLocation());
	const UAnimInstance* Animation = SelfRef->Mesh->GetAnimInstance();
	
	float MovementCurve;
	float TurnSpeedCurve;
	
	Animation->GetCurveValue(FName("ChargeAttack"), MovementCurve);
	Animation->GetCurveValue(FName("TurnSpeed"), TurnSpeedCurve);

	Controller->Move(SelfRef->ChargeAttackMovementSpeed * MovementCurve, DeltaTime);
	Controller->FocusOnPlayer(DeltaTime, SelfRef->ChargeAttackTurnSpeed * TurnSpeedCurve);
}
