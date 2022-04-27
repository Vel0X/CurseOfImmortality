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
	Controller->GetSelfRef()->Jump = true;

	Controller->GetSelfRef()->GetCollisionCapsule()->SetCollisionProfileName(TEXT("OverlapAll"));
}

void UDeprivedJumpAttack::OnStateExit()
{
	Super::OnStateExit();

	UE_LOG(LogTemp, Warning, TEXT("Exit State Jump Attack"))

	Controller->GetSelfRef()->Jump = false;
	Controller->GetSelfRef()->GetCollisionCapsule()->SetCollisionProfileName(TEXT("Pawn"));

	LocationSet = false;
	RemainingTime = ChargeTime;
	PlayerLocation = FVector::Zero();
	JumpDestination = FVector::Zero();
}

void UDeprivedJumpAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	TArray<AActor*> OverlappingActors;
	Controller->GetSelfRef()->AttackSphere->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (Cast<APlayerCharacter>(OverlappingActor))
		{
			if (Cast<ABaseEnemyPawn>(OverlappingActor))
			{
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Do Dmg to Player in State Jump Attack");
			}
		};
	}

	JumpDestination.Z = 0;
	FVector OwnLocation = Controller->GetSelfRef()->GetActorLocation();
	OwnLocation.Z = 0;

	Jump(DeltaTime);
	//
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
	//                                  FString::SanitizeFloat(FVector::Dist(JumpDestination, OwnLocation)));

	if (FVector::Dist(JumpDestination, OwnLocation) <= 50.f)
	{
		Controller->Transition(Controller->Recover, Controller);
	}
}

void UDeprivedJumpAttack::Jump(float DeltaTime)
{
	if (RemainingTime <= 0)
	{
		if (!LocationSet)
		{
			PlayerLocation = Controller->GetPlayer()->GetActorLocation();

			const FVector PlayerForwardDir(Controller->GetPlayer()->GetActorForwardVector() * 300.f + PlayerLocation);
			const FVector OwnLocation(Controller->GetSelfRef()->GetActorLocation());

			JumpDestination = PlayerForwardDir - OwnLocation;
			JumpDestination.Normalize();
			JumpDestination = JumpDestination * 200.f + PlayerForwardDir;
			JumpDir = JumpDestination - OwnLocation;

			LocationSet = true;
		}
		else
		{
			Controller->MoveToTarget(JumpDir, 2000.f, DeltaTime);
		}
	}
	else
	{
		RemainingTime -= DeltaTime * 1.f;
	}
}
