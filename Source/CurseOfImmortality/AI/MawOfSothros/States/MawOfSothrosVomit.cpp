// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosVomit.h"

#include "NiagaraComponent.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/SeaOfDarkness.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/AbilitySpecification.h"

void UMawOfSothrosVomit::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);
	Handle = FMath::Rand();

	Controller = Cast<UMawOfSothrosStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();
	SelfRef->AnimationEnd = false;

	SelfRef->Vomit = true;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Vomit State Entered"))
	}
}

void UMawOfSothrosVomit::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Vomit = false;

	SelfRef->CurrentAttackCooldown = SelfRef->AttackCooldown;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Vomit State Exit"))
	}
}

void UMawOfSothrosVomit::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Idle, Controller);
	}

	Controller->FocusOnPlayer(DeltaTime, 90.f);

	if (SelfRef->SpawnPuddle)
	{
		if (SpawnFrequency <= 0)
		{
			SpawnFrequency = 0.25f;
			
			FVector SpawnLocation(SelfRef->PuddleLowerSpawnLocation->GetComponentLocation());
			auto LowerPuddle = FPersistentWorldManager::ObjectFactory->SpawnAbility(
				SeaOfDarkness, SpawnLocation, FRotator::ZeroRotator, SelfRef);

			SpawnLocation = SelfRef->PuddleUpperSpawnLocation->GetComponentLocation();
			auto UpperPuddle = FPersistentWorldManager::ObjectFactory->SpawnAbility(
				SeaOfDarkness, SpawnLocation, FRotator::ZeroRotator, SelfRef);

			LowerPuddle->AbilityHandle = Handle;
			UpperPuddle->AbilityHandle = Handle;
		}
		SpawnFrequency -= DeltaTime;
	}
}
