// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRunning.h"

#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UDeprivedRunning::OnStateEnter(UStateMachine* StateMachine)
{
	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Running = true;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Running State Entered"))
	}
}

void UDeprivedRunning::OnStateExit()
{
	SelfRef->Running = false;
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Running State Exit"))
	}
}

void UDeprivedRunning::OnStateUpdate(float DeltaTime)
{
	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("Refrence Missing in State Running"));
		return;
	}

	const FVector PlayerLocation = Player->GetActorLocation();

	// FVector OwnLocation(SelfRef->GetActorLocation());
	// FVector RightVectorSelf(SelfRef->GetActorRightVector());
	// FVector LeftVectorSelf(RightVectorSelf.operator-());
	// FVector RightVectorPlayer(Player->GetActorRightVector());
	// FVector LeftVectorPlayer(RightVectorPlayer.operator-());
	// FVector StartPointLeft(LeftVectorSelf * SelfRef->CapsuleComponent->GetUnscaledCapsuleRadius() + OwnLocation);
	// FVector EndPointLeft(LeftVectorPlayer * Player->CapsuleComponent->GetUnscaledCapsuleRadius() + PlayerLocation);
	// FVector StartPointRight(RightVectorSelf * SelfRef->CapsuleComponent->GetUnscaledCapsuleRadius() + OwnLocation);

	FHitResult HitMid;
	// FHitResult HitLeft;
	// FHitResult HitRight;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	CollisionParams.AddIgnoredActor(SelfRef);

	Controller->GetWorld()->LineTraceSingleByChannel(HitMid, SelfRef->GetActorLocation(), Player->GetActorLocation(),
	                                                 ECC_Pawn, CollisionParams);
	// Controller->GetWorld()->LineTraceSingleByChannel(HitLeft, StartPointLeft, EndPointLeft,
	//                                                  ECC_Pawn, CollisionParams);
	// Controller->GetWorld()->LineTraceSingleByChannel(HitRight, StartPointRight, EndPointLeft,
	//                                                  ECC_Pawn, CollisionParams);

	if (/*HitMid.bBlockingHit*/false)
	{
		if (PathfindingTimer <= 0)
		{
			Path.Empty();
			APathfindingGrid* Grid = FPersistentWorldManager::PathfindingGrid;

			if (!Grid->GetPathWorldSpace(SelfRef->GetActorLocation(), Player->GetActorLocation(), Path, false))
			{
				Path.Empty();
				UE_LOG(LogTemp, Error, TEXT("Path is Missing"));
			}
			PathIndex = 0;
			PathfindingTimer = 0.5f;
		}
		if (!Path.IsEmpty())
		{
			FollowPath(DeltaTime);
		}
	}
	else
	{
		Controller->FocusOnPlayer();
		Controller->MoveToTarget(PlayerLocation, SelfRef->MovementSpeed, DeltaTime);
		if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistNormalAttack)
		{
			Controller->Transition(Controller->NormalAttack, Controller);
		}
		else if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistJumpAttack)
		{
			if (SelfRef->CurrentJumpAttackCoolDown <= 0.f)
			{
				SelfRef->CurrentJumpAttackCoolDown = SelfRef->JumpAttackCoolDown;
				Controller->Transition(Controller->JumpAttack, Controller);
			}
		}
	}
	PathfindingTimer -= DeltaTime;
}

void UDeprivedRunning::FollowPath(float DeltaTime)
{
	Controller->MoveToTarget(Path[PathIndex], SelfRef->MovementSpeed, DeltaTime);
	FVector L(SelfRef->GetActorLocation());
	L.Z = 0;
	Controller->FocusOnPath(Path[PathIndex], DeltaTime);

	if (FVector::Dist(Path[PathIndex], L) < 50.f)
	{
		if (PathIndex < Path.Num() - 1)
			PathIndex++;
	}
}
