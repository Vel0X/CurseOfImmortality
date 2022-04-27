// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRunning.h"

#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedRunning::OnStateEnter(UStateMachine* StateMachine)
{
	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Controller->GetSelfRef()->Running = true;
	UE_LOG(LogTemp, Warning, TEXT("Running State Entered"))
}

void UDeprivedRunning::OnStateExit()
{
	Controller->GetSelfRef()->Running = false;
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

	const ABaseCharacter* Player = Controller->GetPlayer();
	const ADeprivedPawn* SelfRef = Controller->GetSelfRef();

	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistNormalAttack)
	{
		if (FVector::Dist(PlayerLocation, Controller->GetSelfRef()->GetActorLocation()) < SelfRef->MinDistNormalAttack)
		{
			Controller->Transition(Controller->NormalAttack, Controller);
		}
		Controller->MoveToTarget(Target, SelfRef->Speed, DeltaTime);
	}
	else if (FVector::Dist(PlayerLocation, Controller->GetSelfRef()->GetActorLocation()) < 800.f)
	{
		if (Controller->GetSelfRef()->JumpAttackCoolDown)
		{
		}
		else
		{
		}
		Controller->Transition(Controller->JumpAttack, Controller);
	}
	else
	{
		Controller->MoveToTarget(Target, 400.f, DeltaTime);
	}
}
