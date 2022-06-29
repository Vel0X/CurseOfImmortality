// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "DeprivedPawn.h"
#include "NiagaraComponent.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "States/DeprivedHitPlayer.h"
#include "States/DeprivedIdle.h"
#include "States/DeprivedJumpAttack.h"
#include "States/DeprivedNormalAttack.h"
#include "States/DeprivedRecover.h"
#include "States/DeprivedRunning.h"
#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"
#include "States/DeprivedFeast.h"
#include "States/DeprivedFrenziedAttack.h"
#include "States/FindStartLocation.h"

void UDeprivedStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!Player)
	{
		Player = FPersistentWorldManager::PlayerCharacter;
		CurrentState = FindStartLocation;
		CurrentState->OnStateEnter(this);
	}
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	if (!CurrentState) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }

	if (!SelfRef->Dead)
	{
		if (Player->Dead)
		{
			if (!StateChanged)
			{
				StateChanged = true;
				Transition(Feast, this);
			}
		}
		else
		{
			LastLocation = Player->GetActorLocation();
		}
		CurrentState->OnStateUpdate(DeltaTime);
	}
	else
	{
		SelfRef->HandGlowLeft->Deactivate();
		SelfRef->HandGlowRight->Deactivate();
	}
	SelfRef->CurrentJumpAttackCoolDown -= DeltaTime;
	SelfRef->CurrentFrenziedAttackCoolDown -= DeltaTime;
}

void UDeprivedStateMachine::BeginPlay()
{
	Super::BeginPlay();

	//Initialise References
	SelfRef = Cast<ADeprivedPawn>(GetOwner());

	//Initialise States
	Idle = NewObject<UDeprivedIdle>();
	Running = NewObject<UDeprivedRunning>();
	JumpAttack = NewObject<UDeprivedJumpAttack>();
	HitPlayer = NewObject<UDeprivedHitPlayer>();
	Recover = NewObject<UDeprivedRecover>();
	NormalAttack = NewObject<UDeprivedNormalAttack>();
	FrenziedAttack = NewObject<UDeprivedFrenziedAttack>();
	Feast = NewObject<UDeprivedFeast>();
	FindStartLocation = NewObject<UFindStartLocation>();
}

TArray<FHitResult> UDeprivedStateMachine::GetHitsInLine(FVector Target) const
{
	FVector MidStart(SelfRef->GetActorLocation());
	MidStart.Z = 20;
	FVector RightStart(SelfRef->GetActorRightVector() * Offset + SelfRef->GetActorLocation());
	RightStart.Z = 20;
	FVector LeftStart(SelfRef->GetActorRightVector().operator-() * Offset + SelfRef->GetActorLocation());
	LeftStart.Z = 20;
	FVector MidEnd(Target);
	MidEnd.Z = 20;
	FVector RightEnd(RightStart + SelfRef->GetActorForwardVector() * Offset);
	RightEnd.Z = 20;
	FVector LeftEnd(LeftStart + SelfRef->GetActorForwardVector() * Offset);
	LeftEnd.Z = 20;

	FHitResult HitMid;
	FHitResult HitLeft;
	FHitResult HitRight;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	CollisionParams.AddIgnoredActor(SelfRef);

	// DrawDebugLine(GetWorld(), LeftStart, LeftEnd, FColor::Red);
	// DrawDebugLine(GetWorld(), RightStart, RightEnd, FColor::Green);
	// DrawDebugLine(GetWorld(), MidStart, MidEnd, FColor::Blue);

	GetWorld()->LineTraceSingleByChannel(HitMid, MidStart, MidEnd, ECC_GameTraceChannel3, CollisionParams);
	GetWorld()->LineTraceSingleByChannel(HitLeft, LeftStart, LeftEnd, ECC_GameTraceChannel3, CollisionParams);
	GetWorld()->LineTraceSingleByChannel(HitRight, RightStart, RightEnd, ECC_GameTraceChannel3, CollisionParams);

	TArray<FHitResult> Hits;

	Hits.Add(HitMid);
	Hits.Add(HitLeft);
	Hits.Add(HitRight);

	return Hits;
}

bool UDeprivedStateMachine::CheckLineOfSight(FVector Target) const
{
	TArray Hits(GetHitsInLine(Target));

	bool Blocking = false;

	for (FHitResult Hit : Hits)
	{
		if (Hit.bBlockingHit)
		{
			Blocking = true;
		}
	}

	return Blocking;
}


void UDeprivedStateMachine::FindPathToPlayer(TArray<FVector>& Path) const
{
	Path.Empty();
	APathfindingGrid* Grid = FPersistentWorldManager::PathfindingGrid;

	if (!Grid)
	{
		UE_LOG(LogTemp, Error, TEXT("No Grid in Deprived State Machine"));
		return;
	}

	if (!Grid->GetPathWorldSpace(SelfRef->GetActorLocation(), Player->GetActorLocation(), Path, false))
	{
		Path.Empty();
		// UE_LOG(LogTemp, Error, TEXT("Path is Missing"));
	}
}

void UDeprivedStateMachine::FindRandomPath(TArray<FVector>& Path, FVector& RandomLocation) const
{
	Path.Empty();
	APathfindingGrid* Grid = FPersistentWorldManager::PathfindingGrid;

	if (!Grid)
	{
		UE_LOG(LogTemp, Error, TEXT("No Grid in Deprived State Machine"));
		return;
	}

	FPfNode* EndNode = Grid->GetRandomNodeInNavMesh();

	if (EndNode->IsWalkable && !EndNode->SpawnArea)
	{
		Grid->GetWorldPositionFromCoordinates(EndNode->X, EndNode->Y, RandomLocation);

		if (!Grid->GetPathWorldSpace(SelfRef->GetActorLocation(), RandomLocation, Path, false))
		{
			Path.Empty();
			// UE_LOG(LogTemp, Error, TEXT("Path is Missing"));
		}
	}
	else
	{
		// UE_LOG(LogTemp, Error, TEXT("Node is not Walkable"));
		Path.Empty();
	}
}

bool UDeprivedStateMachine::FollowPath(TArray<FVector> Path, float DeltaTime, int PathIndex, float RotationSpeed,
                                       float CurveValue, bool IgnoreWalls) const
{
	FVector L(SelfRef->GetActorLocation());
	L.Z = 0;

	MoveToTarget(Path[PathIndex], SelfRef->Stats[Movespeed] * CurveValue, DeltaTime, RotationSpeed, IgnoreWalls);

	if (FVector::Dist(Path[PathIndex], L) < 100.f)
	{
		if (PathIndex < Path.Num() - 1)
			return true;
	}

	return false;
}

void UDeprivedStateMachine::MoveToTarget(FVector Target, const float MovementSpeed, const float DeltaTime,
                                         const float RotationSpeed, bool IgnoreWalls) const
{
	// Target = SelfRef->GetActorLocation() - Target;
	FocusOnLocation(Target, DeltaTime, RotationSpeed);
	Target = Target - SelfRef->GetActorLocation();
	Target.Z = 0;
	SelfRef->MovementComponent->SetDirection(SelfRef->GetActorForwardVector(), MovementSpeed, IgnoreWalls, false);
}

void UDeprivedStateMachine::FocusOnLocation(const FVector Location, const float DeltaTime,
                                            const float RotationSpeed) const
{
	if (!SelfRef)
	{
		UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine"));
		return;
	}
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player in Deprived StateMachine"));
		return;
	}
	FVector Target = Location - SelfRef->GetActorLocation();
	Target.Normalize();
	const FRotator LookAtRotation(
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, RotationSpeed).Rotation());
	const FRotator ZeroedRotation = FRotator(0.f, LookAtRotation.Yaw, 0.f);
	SelfRef->SetActorRotation(ZeroedRotation);
}

//Getter and Setter
ADeprivedPawn* UDeprivedStateMachine::GetSelfRef() const
{
	if (!SelfRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Self Ref in Deprived StateMachine"))
	}
	return SelfRef;
}

APlayerCharacter* UDeprivedStateMachine::GetPlayer() const
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player in Deprived StateMachine"))
	}
	return Player;
}
