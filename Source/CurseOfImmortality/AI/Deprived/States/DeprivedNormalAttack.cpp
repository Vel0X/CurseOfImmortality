// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedNormalAttack.h"

#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedNormalAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();
	SelfRef->DamageComponent->ResetAllHitCharacters();

	SelfRef->NormalAttack = true;

	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("NormalAttack State Entered"))
	}
}

void UDeprivedNormalAttack::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->NormalAttack = false;
	SelfRef->CurrentNormalAttackDuration = SelfRef->NormalAttackDuration;

	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit State NormalAttack"))
	}
}

void UDeprivedNormalAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	Controller->FocusOnPlayer();

	const UAnimInstance* Animation = SelfRef->Mesh->GetAnimInstance();
	float CurveValue;
	Animation->GetCurveValue(FName("MovementSpeed"), CurveValue);

	const FVector PlayerLocation = Player->GetActorLocation();

	if (LeftHandCanAttack)
	{
		SelfRef->DamageComponent->ResetAllHitCharacters();
		LeftHandCanAttack = false;
/*
		TArray<AActor*> OverlappingActors;
		SelfRef->NormalAttackSphereLeft->GetOverlappingActors(OverlappingActors);

		for (AActor* OverlappingActor : OverlappingActors)
		{
			if (Cast<APlayerCharacter>(OverlappingActor))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Damage Left"))
				SelfRef->DealDamage(SelfRef->DamageNormalAttack, Player);
				LeftHandCanAttack = false;
			};
		}*/
	}
	if (RightHandCanAttack)
	{
		SelfRef->DamageComponent->ResetAllHitCharacters();
		RightHandCanAttack = false;
/*
		//UE_LOG(LogTemp, Warning, TEXT("Right Hand Can Attack"))

		TArray<AActor*> OverlappingActors;
		SelfRef->NormalAttackSphereRight->GetOverlappingActors(OverlappingActors);

		for (AActor* OverlappingActor : OverlappingActors)
		{
			if (Cast<APlayerCharacter>(OverlappingActor))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Damage Right"))
				SelfRef->DealDamage(SelfRef->DamageNormalAttack, Player);
				RightHandCanAttack = false;
			};
		}
		*/
	}

	if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) > SelfRef->MinDistNormalAttack)
	{
		Controller->MoveToTarget(PlayerLocation, (SelfRef->Stats[EStats::Movespeed] + 500) * CurveValue, DeltaTime);
	}
	if (SelfRef->CurrentNormalAttackDuration <= 0.f)
	{
		Controller->Transition(Controller->Running, Controller);
	}
	SelfRef->CurrentNormalAttackDuration -= DeltaTime;
}
