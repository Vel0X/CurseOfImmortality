// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosStart.h"

#include "NiagaraComponent.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMawOfSothrosStart::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMawOfSothrosStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->AnimationEnd = false;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Start State Entered"))
	}
}

void UMawOfSothrosStart::OnStateExit()
{
	Super::OnStateExit();

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Exit Start State"))
	}
}

void UMawOfSothrosStart::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	FVector PlayerLocation = Player->GetActorLocation();
	PlayerLocation.Z = 0;
	FVector OwnLocation = SelfRef->GetActorLocation();
	OwnLocation.Z = 0;

	const float Dist = FVector::Dist(PlayerLocation, OwnLocation);

	if (Dist <= 1500.f)
	{
		SelfRef->Start = true;
		if (SelfRef->AnimationStart)
		{
			SelfRef->MawSmoke->Activate();
			SelfRef->Mesh->SetVisibility(true);
			SelfRef->Immune = false;
		}
	}

	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Idle, Controller);
	}
}
