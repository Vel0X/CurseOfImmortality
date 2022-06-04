// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosGroundSlam.h"

#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/MawSlam.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/AbilitySpecification.h"

void UMawOfSothrosGroundSlam::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMawOfSothrosStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->AnimationEnd = false;

	SelfRef->GroundSlam = true;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Ground Slam State Entered"))
	}
}

void UMawOfSothrosGroundSlam::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->CurrentAttackCooldown = SelfRef->AttackCooldown;

	SelfRef->GroundSlam = false;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Ground Slam State Entered"))
	}
}

void UMawOfSothrosGroundSlam::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Idle, Controller);
	}

	const UAnimInstance* Animation = SelfRef->Mesh->GetAnimInstance();

	float TurnSpeedCurve;
	Animation->GetCurveValue(FName("TurnSpeed"), TurnSpeedCurve);

	Controller->FocusOnPlayer(DeltaTime, 90.f * TurnSpeedCurve);
}
