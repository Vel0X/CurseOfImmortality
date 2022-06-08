// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedJumpAttack.h"

#include <string>

#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "Kismet/GameplayStatics.h"

void UDeprivedJumpAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump Attack State Entered"))
	}

	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();
	SelfRef->DamageComponent->ResetAllHitCharacters();

	SelfRef->Jump = true;

	SelfRef->AnimationEnd = false;
}

void UDeprivedJumpAttack::OnStateExit()
{
	Super::OnStateExit();
	if (FPersistentWorldManager::GetLogLevel(DeprivedStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit State Jump Attack"))
	}

	Controller->GetSelfRef()->Jump = false;
	// Controller->GetSelfRef()->CapsuleComponent->SetCollisionProfileName(TEXT("Character"));

	LocationSet = false;

	PlayerLocation = FVector::Zero();
	JumpDestination = FVector::Zero();
}

void UDeprivedJumpAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	JumpDestination.Z = 0;
	OwnLocation = SelfRef->GetActorLocation();
	OwnLocation.Z = 0;

	Jump(DeltaTime);

	Time -= DeltaTime;

	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Recover, Controller);
	}
}

void UDeprivedJumpAttack::SetLocation()
{
	// PlayerLocation = Player->GetActorLocation();
	// FVector PlayerForwardDir(
	// 	Player->GetActorForwardVector() * (SelfRef->PlayerForwardVector * (Player->CurrentMovementSpeed / Player->
	// 		Stats[EStats::Movespeed])) +
	// 	PlayerLocation);
	// OwnLocation = SelfRef->GetActorLocation();
	//
	// JumpDestination = PlayerForwardDir - OwnLocation;
	// JumpDestination.Normalize();
	// JumpDestination = JumpDestination * SelfRef->DistAfterPlayer + PlayerForwardDir;
	//
	// if (Verbose)
	// {
	// 	DrawDebugLine(Controller->GetWorld(), PlayerLocation, PlayerForwardDir, FColor::Red, true, 10);
	// 	DrawDebugLine(Controller->GetWorld(), OwnLocation, PlayerForwardDir, FColor::Green, true, 10);
	// 	DrawDebugLine(Controller->GetWorld(), PlayerForwardDir, JumpDestination,
	// 	              FColor::Blue, true, 10);
	// }
	LocationSet = true;
}

void UDeprivedJumpAttack::Jump(float DeltaTime) const
{
	const UAnimInstance* Animation = SelfRef->Mesh->GetAnimInstance();
	float CurveValue;
	if (LocationSet)
	{
		Animation->GetCurveValue(FName("MovementSpeed"), CurveValue);
		SelfRef->SetActorLocation(
			SelfRef->GetActorLocation() + SelfRef->GetActorForwardVector() * SelfRef->JumpAttackSpeed *
			DeltaTime
		);
	}
	else
	{
		Controller->FocusOnLocation(Player->GetActorLocation(), DeltaTime);
	}
}
