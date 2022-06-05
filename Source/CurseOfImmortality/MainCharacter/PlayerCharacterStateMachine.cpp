// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterStateMachine.h"

#include "PlayerCharacter.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "InputManager.h"
#include "States/PlayerCharacterDash.h"
#include "States/PlayerCharacterIdle.h"
#include "States/PlayerCharacterMelee.h"
#include "States/PlayerCharacterRanged.h"
#include "States/PlayerCharacterRunning.h"
#include "States/PlayerCharacterSpecial.h"

UPlayerCharacterStateMachine::UPlayerCharacterStateMachine()
{
}

void UPlayerCharacterStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentState->OnStateUpdate(DeltaTime);
}

void UPlayerCharacterStateMachine::Initialize()
{
	CurrentState = Idle;
	CurrentState->OnStateEnter(this);
}

void UPlayerCharacterStateMachine::BeginPlay()
{
	Super::BeginPlay();

	//Initialise References
	SelfRef = Cast<APlayerCharacter>(GetOwner());
	NewAction = &SelfRef->InputManager->LastAction;

	//Initialise States
	Idle = NewObject<UPlayerCharacterIdle>();
	Running = NewObject<UPlayerCharacterRunning>();
	MeleeAttack = NewObject<UPlayerCharacterMelee>();
	RangedAttack = NewObject<UPlayerCharacterRanged>();
	SpecialAttack = NewObject<UPlayerCharacterSpecial>();
	Dash = NewObject<UPlayerCharacterDash>();
	
}

//Getter and Setter
APlayerCharacter* UPlayerCharacterStateMachine::GetSelfRef() const
{
	if (!SelfRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Self Ref in Player Character StateMachine"))
	}
	return SelfRef;
}
