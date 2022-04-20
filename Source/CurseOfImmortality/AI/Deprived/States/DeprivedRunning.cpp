// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRunning.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

UDeprivedRunning::UDeprivedRunning(UDeprivedStateMachine* Controller)
{
	this->Controller = Controller;
}

void UDeprivedRunning::OnStateEnter()
{
	Controller->GetSelfRef()->SetMoving(true);
	UE_LOG(LogTemp, Warning, TEXT("Moving State Entered"))
}

void UDeprivedRunning::OnStateExit()
{
	Controller->GetSelfRef()->SetMoving(false);
	UE_LOG(LogTemp, Warning, TEXT("Moving State Exit"))
}

void UDeprivedRunning::OnStateUpdate(float DeltaTime)
{
	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("Refrence Missing in StateMovin: 32"));
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