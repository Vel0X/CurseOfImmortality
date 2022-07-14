// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedIdle.h"

#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UDeprivedIdle::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Idle = true;
	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Deprived Idle State Entered"))
	}
}

void UDeprivedIdle::OnStateExit()
{
	Super::OnStateExit();
	SelfRef->Idle = false;
	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Deprived Exit Idle State"))
	}
}

void UDeprivedIdle::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	const FVector PlayerLocation = Player->GetActorLocation();

	SelfRef->CurrentJumpAttackCoolDown = FMath::RandRange(0.f, SelfRef->JumpAttackCoolDown / 2);
	SelfRef->CurrentFrenziedAttackCoolDown = FMath::RandRange(0.f, SelfRef->FrenziedAttackCoolDown / 2);

	if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistRunning)
	{
		Controller->Transition(Controller->Running, Controller);
	}
	if (SelfRef->CurrentHealth < SelfRef->Stats[Health])
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
