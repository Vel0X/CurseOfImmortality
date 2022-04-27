// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedNormalAttack.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedNormalAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Controller->GetSelfRef()->NormalAttack = true;
	UE_LOG(LogTemp, Warning, TEXT("NormalAttack State Entered"))
}

void UDeprivedNormalAttack::OnStateExit()
{
	Super::OnStateExit();

	Controller->GetSelfRef()->NormalAttack = false;
	CurrentDuration = Duration;
	UE_LOG(LogTemp, Warning, TEXT("Exit State NormalAttack"))
}

void UDeprivedNormalAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	const FVector PlayerLocation = Controller->GetPlayer()->GetActorLocation();
	const FVector Target = PlayerLocation - Controller->GetSelfRef()->GetActorLocation();

	if (FVector::Dist(PlayerLocation, Controller->GetSelfRef()->GetActorLocation()) > 100.f)
	{
		Controller->MoveToTarget(Target, 400.f, DeltaTime);
	}
	if (CurrentDuration <= 0.f)
	{
		Controller->Transition(Controller->Running, Controller);
	}

	CurrentDuration -= DeltaTime;
}
