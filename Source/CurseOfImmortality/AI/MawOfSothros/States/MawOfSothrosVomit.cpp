// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosVomit.h"

#include "NiagaraComponent.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"
#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/SeaOfDarkness.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/AbilitySpecification.h"

void UMawOfSothrosVomit::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMawOfSothrosStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Vomit = true;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Vomit State Entered"))
	}
}

void UMawOfSothrosVomit::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Vomit = false;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Vomit State Exit"))
	}
}

void UMawOfSothrosVomit::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnPlayer(DeltaTime, 90.f);

	if (SpawnPuddle)
	{
		if (SpawnFrequency <= 0)
		{
			SpawnFrequency = 0.5f;

			FVector SpawnLocation(SelfRef->PuddleLowerSpawnLocation->GetComponentLocation());
			ASeaOfDarkness* AbilityInstance = Cast<ASeaOfDarkness>(SelfRef->GetWorld()->SpawnActor(
				SelfRef->AbilitySpecification->Class,
				&SpawnLocation, &FRotator::ZeroRotator));
			if (!AbilityInstance) { return; }
			AbilityInstance->InitializeAbility(1, SelfRef, 1);

			SpawnLocation = SelfRef->PuddleUpperSpawnLocation->GetComponentLocation();
			AbilityInstance = Cast<ASeaOfDarkness>(SelfRef->GetWorld()->SpawnActor(
				SelfRef->AbilitySpecification->Class,
				&SpawnLocation, &FRotator::ZeroRotator));
			if (!AbilityInstance) { return; }
			AbilityInstance->InitializeAbility(1, SelfRef, 1);

			for (int index = 0; index < 2; ++index)
			{
			}
		}
		SpawnFrequency -= DeltaTime;
	}
}

void UMawOfSothrosVomit::ActivateVomit()
{
	SelfRef->VomitLowerJaw->Activate();
	SelfRef->VomitUpperJaw->Activate();

	SpawnPuddle = true;
}

void UMawOfSothrosVomit::DeactivateVomit()
{
	SelfRef->VomitLowerJaw->Deactivate();
	SelfRef->VomitUpperJaw->Deactivate();

	SpawnPuddle = false;
}

void UMawOfSothrosVomit::TransitionToIdle()
{
	Controller->Transition(Controller->Idle, Controller);
}
