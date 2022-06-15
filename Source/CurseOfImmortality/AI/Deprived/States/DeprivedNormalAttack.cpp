// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedNormalAttack.h"

#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UDeprivedNormalAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();
	SelfRef->DamageComponent->ResetAllHitCharacters();
	SelfRef->NormalAttack = true;
	SelfRef->AnimationEnd = false;

	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("NormalAttack State Entered"))
	}
}

void UDeprivedNormalAttack::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->NormalAttack = false;

	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit State NormalAttack"))
	}
}

void UDeprivedNormalAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnLocation(Player->GetActorLocation(), DeltaTime);

	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
