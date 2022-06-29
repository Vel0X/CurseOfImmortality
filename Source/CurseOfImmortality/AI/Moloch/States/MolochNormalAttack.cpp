// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/States/MolochNormalAttack.h"

#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"
#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMolochNormalAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMolochStateMachine>(StateMachine);

	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->AnimationEnd = false;

	SelfRef->NormalAttack = true;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("NormalAttack State Entered"))
	}
}

void UMolochNormalAttack::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->NormalAttack = false;

	SelfRef->TargetLocation = FVector::Zero();

	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("NormalAttack State Exit"))
	}
}

void UMolochNormalAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnLocation(Player->GetActorLocation(), DeltaTime, 90.f);

	if (!SelfRef->TargetLocation.IsZero())
	{
		float MovementCurve;

		const UAnimInstance* Animation = SelfRef->Mesh->GetAnimInstance();
		Animation->GetCurveValue(FName("Speed"), MovementCurve);

		Controller->MoveToTarget(SelfRef->TargetLocation, 600.f * MovementCurve, DeltaTime, 720.f, true);
	}

	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Walking, Controller);
	}
}
