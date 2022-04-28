// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRunning.h"

#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedRunning::OnStateEnter(UStateMachine* StateMachine)
{
	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Running = true;
	UE_LOG(LogTemp, Warning, TEXT("Running State Entered"))
}

void UDeprivedRunning::OnStateExit()
{
	SelfRef->Running = false;
	UE_LOG(LogTemp, Warning, TEXT("Running State Exit"))
}

void UDeprivedRunning::OnStateUpdate(float DeltaTime)
{
	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("Refrence Missing in State Running"));
		return;
	}
	Controller->FocusOnPlayer();

	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistNormalAttack)
	{
		Controller->Transition(Controller->NormalAttack, Controller);
	}
	else if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistJumpAttack)
	{
		if (SelfRef->CurrentJumpAttackCoolDown <= 0.f)
		{
			SelfRef->CurrentJumpAttackCoolDown = SelfRef->JumpAttackCoolDown;
			Controller->Transition(Controller->JumpAttack, Controller);
		}
		else
		{
			Controller->MoveToTarget(Target, SelfRef->Speed, DeltaTime);
		}
	}
	else
	{
		Controller->MoveToTarget(Target, SelfRef->Speed, DeltaTime);
	}
}
