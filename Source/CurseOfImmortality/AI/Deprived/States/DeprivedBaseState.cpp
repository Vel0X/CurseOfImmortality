// Fill out your copyright notice in the Description page of Project Settings.


#include "DeprivedBaseState.h"

inline void UDeprivedBaseState::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);
}

inline void UDeprivedBaseState::OnStateExit()
{
	Super::OnStateExit();
}

inline void UDeprivedBaseState::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);
}
