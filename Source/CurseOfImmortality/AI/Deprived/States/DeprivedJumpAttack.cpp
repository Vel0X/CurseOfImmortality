// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedJumpAttack.h"

#include "PlayerCharacter.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

void UDeprivedJumpAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	UE_LOG(LogTemp, Warning, TEXT("Jump Attack State Entered"))

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Controller->GetSelfRef()->SetJump(true);

	Controller->GetSelfRef()->GetCollisionCapsule()->SetCollisionProfileName(TEXT("OverlapAll"));
}

void UDeprivedJumpAttack::OnStateExit()
{
	Super::OnStateExit();

	UE_LOG(LogTemp, Warning, TEXT("Exit State Jump Attack"))

	Controller->GetSelfRef()->SetJump(false);
	Controller->GetSelfRef()->GetCollisionCapsule()->SetCollisionProfileName(TEXT("Pawn"));

	LocationSet = false;
	RemainingTime = ChargeTime;
	PlayerLocation = FVector::Zero();
}

void UDeprivedJumpAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	TArray<AActor*> OverlappingActors;
	Controller->GetSelfRef()->GetAttackSphere()->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (Cast<APlayerCharacter>(OverlappingActor))
		{
			if (Cast<ABaseEnemyPawn>(OverlappingActor))
			{
			}
			else
			{
				Controller->Transition(Controller->GetHitPlayer(), Controller);
			}
		};
	}
	Jump(DeltaTime);

	if (FVector::Dist(PlayerLocation, Controller->GetSelfRef()->GetActorLocation()) <= 50.f)
	{
		Controller->Transition(Controller->GetRecover(), Controller);
	}
}

void UDeprivedJumpAttack::Jump(float DeltaTime)
{
	if (RemainingTime <= 0)
	{
		if (!LocationSet)
		{
			PlayerLocation = Controller->GetPlayer()->GetActorLocation();
			JumpDestination = PlayerLocation - Controller->GetSelfRef()->GetActorLocation();
			LocationSet = true;
		}
		else
		{
			Controller->MoveToTarget(JumpDestination, 2000.f, DeltaTime);
		}
	}
	else
	{
		RemainingTime -= DeltaTime * 1.f;
	}
}
