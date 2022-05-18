// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedJumpAttack.h"

#include <string>

#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

void UDeprivedJumpAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump Attack State Entered"))
	}

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Jump = true;

	// SelfRef->CapsuleComponent->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));
}

void UDeprivedJumpAttack::OnStateExit()
{
	Super::OnStateExit();
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit State Jump Attack"))
	}

	Controller->GetSelfRef()->Jump = false;
	// Controller->GetSelfRef()->CapsuleComponent->SetCollisionProfileName(TEXT("Character"));

	LocationSet = false;
	SelfRef->CurrentJumpAttackChargeTime = SelfRef->JumpAttackChargeTime;
	SelfRef->CurrentJumpAttackDuration = SelfRef->JumpAttackDuration;

	PlayerLocation = FVector::Zero();
	JumpDestination = FVector::Zero();
}

void UDeprivedJumpAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	TArray<AActor*> OverlappingActors;
	SelfRef->JumpAttackSphere->GetOverlappingActors(OverlappingActors);

	if (!OverlappingActors.IsEmpty())
	{
		for (AActor* OverlappingActor : OverlappingActors)
		{
			if (Cast<APlayerCharacter>(OverlappingActor))
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Do Dmg to Player in State Jump Attack");
			};
		}
	}

	JumpDestination.Z = 0;
	OwnLocation = SelfRef->GetActorLocation();
	OwnLocation.Z = 0;

	Jump(DeltaTime);

	if (FVector::Dist(JumpDestination, OwnLocation) <= 50.f || SelfRef->CurrentJumpAttackDuration <= 0)
	{
		Controller->Transition(Controller->Recover, Controller);
	}

	SelfRef->CurrentJumpAttackDuration -= DeltaTime;
}

void UDeprivedJumpAttack::SetLocation()
{
	PlayerLocation = Player->GetActorLocation();
	FVector PlayerForwardDir(
		Player->GetActorForwardVector() * (SelfRef->PlayerForwardVector * (Player->CurrentMovementSpeed / Player->
			MovementSpeed)) +
		PlayerLocation);
	OwnLocation = SelfRef->GetActorLocation();

	JumpDestination = PlayerForwardDir - OwnLocation;
	JumpDestination.Normalize();
	JumpDestination = JumpDestination * SelfRef->DistAfterPlayer + PlayerForwardDir;

	if (Verbose)
	{
		DrawDebugLine(Controller->GetWorld(), PlayerLocation, PlayerForwardDir, FColor::Red, true, 10);
		DrawDebugLine(Controller->GetWorld(), OwnLocation, PlayerForwardDir, FColor::Green, true, 10);
		DrawDebugLine(Controller->GetWorld(), PlayerForwardDir, JumpDestination,
		              FColor::Blue, true, 10);
	}
	LocationSet = true;
}

void UDeprivedJumpAttack::Jump(float DeltaTime) const
{
	const UAnimInstance* Animation = SelfRef->Mesh->GetAnimInstance();
	float CurveValue;
	Animation->GetCurveValue(FName("MovementSpeed"), CurveValue);

	if (LocationSet)
	{
		Controller->MoveToTarget(JumpDestination, SelfRef->JumpAttackSpeed * CurveValue);
	}
	else
	{
		Controller->FocusOnPlayer();
	}
}
