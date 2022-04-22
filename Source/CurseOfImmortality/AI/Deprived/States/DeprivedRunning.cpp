// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRunning.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

void UDeprivedRunning::OnStateEnter(UStateMachine* StateMachine)
{
	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Controller->GetSelfRef()->SetMoving(true);
	UE_LOG(LogTemp, Warning, TEXT("Running State Entered"))
}

void UDeprivedRunning::OnStateExit()
{
	Controller->GetSelfRef()->SetMoving(false);
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

	if (FVector::Dist(PlayerLocation, Controller->GetSelfRef()->GetActorLocation()) < 800)
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump Attack"))
	}
	else
	{
		const FVector Target = PlayerLocation - Controller->GetSelfRef()->GetActorLocation();

		Controller->MoveToTarget(Target, 400.f, DeltaTime);
	}
}
