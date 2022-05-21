// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosIdle.h"

#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"

void UMawOfSothrosIdle::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMawOfSothrosStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Idle = true;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Idle State Entered"))
	}
}

void UMawOfSothrosIdle::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Idle = false;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Exit Idle State"))
	}
}

void UMawOfSothrosIdle::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnPlayer(DeltaTime);
}
