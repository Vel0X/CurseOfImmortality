// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosGroundSlam.h"

UMawOfSothrosGroundSlam::UMawOfSothrosGroundSlam()
{
	AttackType = GroundSlam;
}

void UMawOfSothrosGroundSlam::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);
}

void UMawOfSothrosGroundSlam::OnStateExit()
{
	Super::OnStateExit();
}

void UMawOfSothrosGroundSlam::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
}
