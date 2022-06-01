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
				TArray<UMawOfSothrosBaseState*> MawAttacks;
				MawAttacks.Add(Cast<UMawOfSothrosBaseState>(Controller->ChargeAttack));
				MawAttacks.Add(Cast<UMawOfSothrosBaseState>(Controller->Vomit));
				// MawAttacks.Add(GroundSlam);
				AttackRandomizer(MawAttacks);
			}
			else if (Dist < SelfRef->DistRangedAttack)
			{
				TArray<UMawOfSothrosBaseState*> MawAttacks;
				MawAttacks.Add(Cast<UMawOfSothrosBaseState>(Controller->ChargeAttack));
				MawAttacks.Add(Cast<UMawOfSothrosBaseState>(Controller->Vomit));
				AttackRandomizer(MawAttacks);
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
				TArray<UMawOfSothrosBaseState*> MawAttacks;
				MawAttacks.Add(Cast<UMawOfSothrosBaseState>(Controller->TailSweep));
				AttackRandomizer(MawAttacks);
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

void UMawOfSothrosIdle::AttackRandomizer(TArray<UMawOfSothrosBaseState*> Attacks) const
{
	int WeightSum = 0;

	for (const UMawOfSothrosBaseState* Attack : Attacks)
	{
		WeightSum += Attack->Weight;
	}

	int Rand = FMath::RandRange(0, WeightSum);

	for (UMawOfSothrosBaseState* Attack : Attacks)
	{
		Rand -= Attack->Weight;
		if (Attack->Weight > Rand)
		{
			switch (Attack->AttackType)
			{
			case Vomit:
				Controller->Transition(Controller->Vomit, Controller);
				break;
			case TailSweep:
				Controller->Transition(Controller->TailSweep, Controller);
				break;
			case GroundSlam:
				Controller->Transition(Controller->GroundSlam, Controller);
				break;
			case ChargeAttack:
				Controller->Transition(Controller->ChargeAttack, Controller);
				break;
			default:
				Controller->Transition(Controller->Idle, Controller);;
			}
			Attack->Weight -= 50;
		}
		else
		{
			Attack->Weight += 50;
		}
	}
}
