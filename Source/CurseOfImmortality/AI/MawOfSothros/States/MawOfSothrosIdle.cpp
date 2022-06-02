// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosIdle.h"

#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMawOfSothrosIdle::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMawOfSothrosStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Idle = true;

	MawAttackStates.Add(Controller->Vomit);
	MawAttackStates.Add(Controller->GroundSlam);
	MawAttackStates.Add(Controller->ChargeAttack);
	MawAttackStates.Add(Controller->TailSweep);

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Idle State Entered"))
	}
}

void UMawOfSothrosIdle::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Idle = false;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Maw Exit Idle State"))
	}
}

void UMawOfSothrosIdle::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);


	FVector PlayerLocation = Player->GetActorLocation();
	FVector OwnLocation = SelfRef->GetActorLocation();
	FVector VectorToPlayer = PlayerLocation - OwnLocation;

	const float Angle = Controller->CalculateAngleBetweenVectors(VectorToPlayer, SelfRef->GetActorForwardVector());
	const float Dist = FVector::Dist(PlayerLocation, OwnLocation);

	if (SelfRef->CurrentAttackCooldown <= 0)
	{
		if (Angle < 30.f)
		{
			Controller->FocusOnPlayer(DeltaTime, Angle);

			if (Dist < SelfRef->DistMeleeAttack)
			{
				AttackRandomizer(Controller->MeleeAttackTypes);
			}
			else if (Dist < SelfRef->DistRangedAttack)
			{
				AttackRandomizer(Controller->RangedAttackTypes);
			}
			else
			{
				Controller->Move(SelfRef->CurrentMovementSpeed, DeltaTime);
			}
		}
		else if (Angle > 130.f)
		{
			if (Dist < 400.f)
			{
				AttackRandomizer(Controller->BackAttackTypes);
			}
			else
			{
				Controller->FocusOnPlayer(DeltaTime, Angle);
			}
		}
		else
		{
			Controller->FocusOnPlayer(DeltaTime, Angle);
		}
	}
	else
	{
		SelfRef->CurrentAttackCooldown -= DeltaTime;
		Controller->FocusOnPlayer(DeltaTime, Angle);
		Controller->Move(SelfRef->CurrentMovementSpeed, DeltaTime);
	}
}

void UMawOfSothrosIdle::AttackRandomizer(TArray<FAttackType>& Attacks) const
{
	int WeightSum = 0;

	for (int i = 0; i < Attacks.Num(); ++i)
	{
		WeightSum += Attacks[i].CurrentWeight;
	}

	int Rand = FMath::RandRange(0, WeightSum);

	for (int i = 0; i < Attacks.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Random Number %i on index %i"), Rand, i);

		UE_LOG(LogTemp, Warning, TEXT("%i on %i"), Attacks[i].CurrentWeight, i);
		if (Attacks[i].CurrentWeight >= Rand)
		{
			for (int f = 0; f < Attacks.Num(); ++f)
			{
				if (Attacks[i].Type != Attacks[f].Type)
					Attacks[f].ResetWeight();
			}

			Attacks[i].CurrentWeight /= 2;
			UE_LOG(LogTemp, Warning, TEXT("%i on %i"), Attacks[i].CurrentWeight, i);

			switch (Attacks[i].Type)
			{
			case GroundSlam:
				Controller->Transition(Controller->GroundSlam, Controller);
				return;
			case Vomit:
				Controller->Transition(Controller->Vomit, Controller);
				return;
			case TailSweep:
				Controller->Transition(Controller->TailSweep, Controller);
				return;
			case ChargeAttack:
				Controller->Transition(Controller->ChargeAttack, Controller);
				return;
			default:
				Controller->Transition(Controller->Idle, Controller);
			}
		}
		Rand -= Attacks[i].CurrentWeight;
	}
}
