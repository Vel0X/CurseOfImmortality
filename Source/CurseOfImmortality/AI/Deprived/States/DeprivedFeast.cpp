// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedFeast.h"

#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UDeprivedFeast::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Running = true;

	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Deprived Feast State Entered"))
	}
}

void UDeprivedFeast::OnStateExit()
{
	Super::OnStateExit();
	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Deprived Exit Feast State"))
	}
}

void UDeprivedFeast::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	FVector FeastLocation = Controller->LastLocation;
	FeastLocation.Z = 0;
	FVector OwnLocation = SelfRef->GetActorLocation();
	OwnLocation.Z = 0;

	if (FVector::Dist(FeastLocation, OwnLocation) < 100.f)
	{
		SelfRef->Running = false;
		SelfRef->Feast = true;
	}
	else
	{
		Controller->MoveToTarget(FeastLocation, SelfRef->Stats[Movespeed], DeltaTime);
	}
}
