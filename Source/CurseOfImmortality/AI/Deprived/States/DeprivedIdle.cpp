// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedIdle.h"

#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedIdle::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Idle = true;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Deprived Idle State Entered"))
	}
}

void UDeprivedIdle::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->Idle = false;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Deprived Exit Idle State"))
	}
}

void UDeprivedIdle::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnLocation(Player->GetActorLocation(), DeltaTime);
	const FVector PlayerLocation = Player->GetActorLocation();

	if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistRunning)
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
