// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRunning.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedRunning::OnStateEnter(UStateMachine* StateMachine)
{
	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Controller->GetSelfRef()->SetRunning(true);
	UE_LOG(LogTemp, Warning, TEXT("Running State Entered"))
}

void UDeprivedRunning::OnStateExit()
{
	Controller->GetSelfRef()->SetRunning(false);
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

	const FVector PlayerLocation = Controller->GetPlayer()->GetActorLocation();

	if (FVector::Dist(PlayerLocation, Controller->GetSelfRef()->GetActorLocation()) < 800.f)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *PlayerLocation.ToString());
		Controller->Transition(Controller->GetJumpAttack(), Controller);
	}
	else
	{
		const FVector Target = PlayerLocation - Controller->GetSelfRef()->GetActorLocation();
		
		Controller->MoveToTarget(Target, 400.f, DeltaTime);
	}
}
