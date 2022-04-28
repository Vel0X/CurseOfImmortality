// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedNormalAttack.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedNormalAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();
	SelfRef->NormalAttack = true;
	
	UE_LOG(LogTemp, Warning, TEXT("NormalAttack State Entered"))
}

void UDeprivedNormalAttack::OnStateExit()
{
	Super::OnStateExit();
	
	SelfRef->NormalAttack = false;
	SelfRef->CurrentNormalAttackDuration = SelfRef->NormalAttackDuration;
	
	UE_LOG(LogTemp, Warning, TEXT("Exit State NormalAttack"))
}

void UDeprivedNormalAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) > SelfRef->MinDistNormalAttack)
	{
		Controller->MoveToTarget(Target, SelfRef->Speed, DeltaTime);
	}
	if (SelfRef->CurrentNormalAttackDuration <= 0.f)
	{
		Controller->Transition(Controller->Running, Controller);
	}
	SelfRef->CurrentNormalAttackDuration -= DeltaTime;
}
