// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"

#include "State.h"


// Sets default values for this component's properties
UStateMachine::UStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateMachine::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UStateMachine::Transition(UState* NewState, UStateMachine* Controller)
{
	CurrentState->OnStateExit();
	CurrentState = NewState;
	CurrentState->OnStateEnter(Controller);
}


// Called every frame
void UStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

