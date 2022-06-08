// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedNormalAttack.h"

#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
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

	const UAnimInstance* Animation = SelfRef->Mesh->GetAnimInstance();
	float CurveValue;
	Animation->GetCurveValue(FName("MovementSpeed"), CurveValue);

	const FVector PlayerLocation = Player->GetActorLocation();

	if (LeftHandCanAttack)
	{
		SelfRef->DamageComponent->ResetAllHitCharacters();
		LeftHandCanAttack = false;
	}
	if (RightHandCanAttack)
	{
		SelfRef->DamageComponent->ResetAllHitCharacters();
		RightHandCanAttack = false;
	}

	if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) > SelfRef->MinDistNormalAttack)
	{
		Controller->MoveToTarget(PlayerLocation, (SelfRef->Stats[EStats::Movespeed] + 500) * CurveValue, DeltaTime);
	}
	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
