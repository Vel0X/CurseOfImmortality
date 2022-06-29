// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/States/MolochStomping.h"

#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"
#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"
#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMolochStomping::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMolochStateMachine>(StateMachine);

	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->AnimationEnd = false;

	SelfRef->CapsuleCollision->SetCollisionProfileName(TEXT("NoCollision"));

	SelfRef->Stomping = true;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Stomping State Entered"))
	}
}

void UMolochStomping::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->MovementComponent->MoveThroughCharacters = false;

	SelfRef->CapsuleCollision->SetCollisionProfileName(TEXT("Character"));

	SelfRef->Stomping = false;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Walking State Exit"))
	}
}

void UMolochStomping::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	float Curve;

	const UAnimInstance* Animation = SelfRef->Mesh->GetAnimInstance();
	Animation->GetCurveValue(FName("Rotation"), Curve);

	Controller->FocusOnLocation(Player->GetActorLocation(), DeltaTime, 140.f * Curve);

	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Walking, Controller);
	}
}
