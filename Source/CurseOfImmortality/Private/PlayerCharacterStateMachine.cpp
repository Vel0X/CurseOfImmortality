// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterStateMachine.h"

#include "PlayerCharacter.h"
#include "PlayerCharacterDash.h"
#include "PlayerCharacterIdle.h"
#include "PlayerCharacterRunning.h"
#include "PlayerCharacterMelee.h"
#include "PlayerCharacterRanged.h"
#include "PlayerCharacterSpecial.h"

UPlayerCharacterStateMachine::UPlayerCharacterStateMachine()
{
}

void UPlayerCharacterStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentState->OnStateUpdate(DeltaTime);
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

	CurrentState = Idle;
	CurrentState->OnStateEnter(this);
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
