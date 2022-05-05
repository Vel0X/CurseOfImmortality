// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/States/DeprivedRunning.h"

#include "GameController.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

void UDeprivedRunning::OnStateEnter(UStateMachine* StateMachine)
{
	Controller = Cast<UDeprivedStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Running = true;
	UE_LOG(LogTemp, Warning, TEXT("Running State Entered"))
}

void UDeprivedRunning::OnStateExit()
{
	SelfRef->Running = false;
	UE_LOG(LogTemp, Warning, TEXT("Running State Exit"))
}

void UDeprivedRunning::OnStateUpdate(float DeltaTime)
{
	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("Refrence Missing in State Running"));
		return;
	}

	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	if (!Path.IsEmpty())
	{
		FHitResult Hit;
		FCollisionQueryParams CollisionParams;

		FVector LineTraceStart = SelfRef->GetActorLocation();
		FVector LineTraceEnd = PlayerLocation - LineTraceStart;
		LineTraceEnd.Normalize();
		LineTraceEnd *= SelfRef->DistJumpAttack;

		DrawDebugLine(Controller->GetWorld(), LineTraceStart, LineTraceEnd, FColor::Purple);

		Controller->GetWorld()->LineTraceSingleByChannel(Hit, LineTraceStart, LineTraceEnd, ECC_Pawn, CollisionParams);

		UE_LOG(LogTemp, Error, TEXT("%s"), *Hit.GetActor()->GetName());

		if (FVector::Dist(PlayerLocation, SelfRef->GetActorLocation()) < SelfRef->DistNormalAttack)
		{
			Controller->Transition(Controller->NormalAttack, Controller);
		}
		else if (Cast<APlayerCharacter>(Cast<APlayerCharacter>(Hit.GetActor())))
		{
			if (SelfRef->CurrentJumpAttackCoolDown <= 0.f)
			{
				SelfRef->CurrentJumpAttackCoolDown = SelfRef->JumpAttackCoolDown;
				Controller->Transition(Controller->JumpAttack, Controller);
			}
			else
			{
				FollowPath(DeltaTime);
			}
		}
		else
		{
			FollowPath(DeltaTime);
		}
	}

	if (PathfindingTimer <= 0)
	{
		Path.Empty();
		auto Grid = static_cast<UGameController*>(Controller->GetOwner()->GetGameInstance())->GetPathfindingGrid();

		if (!Grid->GetPathWorldSpace(SelfRef->GetActorLocation(), Player->GetActorLocation(), Path, true))
		{
			UE_LOG(LogTemp, Error, TEXT("Path is Missing"));
		}
		PathIndex = 0;
		PathfindingTimer = 0.5f;
	}
	PathfindingTimer -= DeltaTime;
}

void UDeprivedRunning::FollowPath(float DeltaTime)
{
	Controller->MoveToTarget(Path[PathIndex], SelfRef->Speed);
	FVector L(SelfRef->GetActorLocation());
	L.Z = 0;
	Controller->FocusOnPath(Path[PathIndex], DeltaTime);

	if (FVector::Dist(Path[PathIndex], L) < 50.f)
	{
		if (PathIndex < Path.Num() - 1)
			PathIndex++;
	}
}
