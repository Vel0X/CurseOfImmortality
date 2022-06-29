// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/States/MolochHitPlayer.h"

#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"
#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMolochHitPlayer::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMolochStateMachine>(StateMachine);

	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->AnimationEnd = false;

	const FVector Scale(2, 2, 2);
	SelfRef->HeadAttack->SetWorldScale3D(Scale);

	TargetLocation = FVector::ZeroVector;

	SelfRef->HitPlayer = true;

	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitPlayer State Entered"))
	}
}

void UMolochHitPlayer::OnStateExit()
{
	Super::OnStateExit();

	const FVector Scale(1, 1, 1);
	SelfRef->HeadAttack->SetWorldScale3D(Scale);

	SelfRef->HitPlayer = false;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitPlayer State Exit"))
	}
}

void UMolochHitPlayer::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
	
	if (TargetLocation.IsZero())
	{
		TargetLocation = SelfRef->HeadLocation->GetComponentLocation() + SelfRef->GetActorForwardVector() * 10000.f;
	}

	float MovementCurve;

	const UAnimInstance* Animation = SelfRef->Mesh->GetAnimInstance();
	Animation->GetCurveValue(FName("Speed"), MovementCurve);

	Controller->MoveToTarget(TargetLocation, 1800.f * MovementCurve, DeltaTime, 720.f, true);


	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Walking, Controller);
	}
}
