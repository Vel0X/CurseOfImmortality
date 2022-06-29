// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"

#include "MolochPawn.h"
#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "States/MolochChargeAttack.h"
#include "States/MolochFindStartLocation.h"
#include "States/MolochHitPlayer.h"
#include "States/MolochHitWall.h"
#include "States/MolochIdle.h"
#include "States/MolochKick.h"
#include "States/MolochNormalAttack.h"
#include "States/MolochPrepareCharge.h"
#include "States/MolochStomping.h"
#include "States/MolochWalking.h"

void UMolochStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
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
		CurrentState->OnStateUpdate(DeltaTime);
	}

	UE_LOG(LogTemp, Error, TEXT("%f"), SelfRef->CurrentChargeAttackCoolDown);
	SelfRef->CurrentChargeAttackCoolDown -= DeltaTime;
	SelfRef->CurrentAttackDelay -= DeltaTime;
}

void UMolochStateMachine::BeginPlay()
{
	Super::BeginPlay();

	//Initialise References
	SelfRef = Cast<AMolochPawn>(GetOwner());

	//Initialise States
	Idle = NewObject<UMolochIdle>();
	Walking = NewObject<UMolochWalking>();
	ChargeAttack = NewObject<UMolochChargeAttack>();
	NormalAttack = NewObject<UMolochNormalAttack>();
	HitPlayer = NewObject<UMolochHitPlayer>();
	HitWall = NewObject<UMolochHitWall>();
	FindStartLocation = NewObject<UMolochFindStartLocation>();
	Stomping = NewObject<UMolochStomping>();
	Kick = NewObject<UMolochKick>();
	PrepareCharge = NewObject<UMolochPrepareCharge>();
}

TArray<FHitResult> UMolochStateMachine::GetHitsInLine(FVector Target) const
{
	FVector MidStart(SelfRef->HeadLocation->GetComponentLocation());
	MidStart.Z = 100;
	FVector RightStart(SelfRef->GetActorRightVector() * Offset + SelfRef->HeadLocation->GetComponentLocation());
	RightStart.Z = 100;
	FVector LeftStart(
		SelfRef->GetActorRightVector().operator-() * Offset + SelfRef->HeadLocation->GetComponentLocation());
	LeftStart.Z = 100;
	FVector MidEnd(Target);
	MidEnd.Z = 100;
	FVector RightEnd(SelfRef->GetActorForwardVector() * Offset + RightStart);
	RightEnd.Z = 100;
	FVector LeftEnd(SelfRef->GetActorForwardVector() * Offset + LeftStart);
	LeftEnd.Z = 100;

	FHitResult HitMid;
	FHitResult HitLeft;
	FHitResult HitRight;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	CollisionParams.AddIgnoredActor(SelfRef);

	DrawDebugLine(GetWorld(), LeftStart, LeftEnd, FColor::Red);
	DrawDebugLine(GetWorld(), RightStart, RightEnd, FColor::Green);
	DrawDebugLine(GetWorld(), MidStart, MidEnd, FColor::Blue);

	GetWorld()->LineTraceSingleByChannel(HitMid, MidStart, MidEnd, ECC_GameTraceChannel3, CollisionParams);
	GetWorld()->LineTraceSingleByChannel(HitLeft, LeftStart, LeftEnd, ECC_GameTraceChannel3, CollisionParams);
	GetWorld()->LineTraceSingleByChannel(HitRight, RightStart, RightEnd, ECC_GameTraceChannel3, CollisionParams);

	TArray<FHitResult> Hits;

	Hits.Add(HitMid);
	Hits.Add(HitLeft);
	Hits.Add(HitRight);

	return Hits;
}

bool UMolochStateMachine::CheckLineOfSight(FVector Target) const
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

void UMolochStateMachine::FindPathToPlayer(TArray<FVector>& Path) const
{
	Path.Empty();
	APathfindingGrid* Grid = FPersistentWorldManager::PathfindingGrid;
	if (!Grid)
	{
		UE_LOG(LogTemp, Error, TEXT("No Grid in Moloch State Machine"));
		return;
	}

	if (!Grid->GetPathWorldSpace(SelfRef->HeadLocation->GetComponentLocation(), Player->GetActorLocation(), Path,
	                             false))
	{
		Path.Empty();
		UE_LOG(LogTemp, Error, TEXT("Path is Missing"));
	}
}

void UMolochStateMachine::FindRandomPath(TArray<FVector>& Path, FVector& RandomLocation) const
{
	Path.Empty();
	APathfindingGrid* Grid = FPersistentWorldManager::PathfindingGrid;
	if (!Grid)
	{
		UE_LOG(LogTemp, Error, TEXT("No Grid in Moloch State Machine"));
		return;
	}

	FPfNode* EndNode = Grid->GetRandomNodeInNavMesh();

	if (EndNode->IsWalkable && !EndNode->SpawnArea)
	{
		Grid->GetWorldPositionFromCoordinates(EndNode->X, EndNode->Y, RandomLocation);

		if (!Grid->GetPathWorldSpace(SelfRef->HeadLocation->GetComponentLocation(), RandomLocation, Path, false))
		{
			Path.Empty();
			UE_LOG(LogTemp, Error, TEXT("Path is Missing"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Node is not Walkable"));
		Path.Empty();
	}
}

bool UMolochStateMachine::FollowPath(TArray<FVector> Path, float DeltaTime, int PathIndex, bool IgnoreWall,
                                     float RotationSpeed,
                                     float CurveValue) const
{
	FVector L(SelfRef->HeadLocation->GetComponentLocation());
	L.Z = 0;

	MoveToTarget(Path[PathIndex], SelfRef->Stats[Movespeed] * CurveValue, DeltaTime, RotationSpeed, IgnoreWall);

	if (FVector::Dist(Path[PathIndex], L) < 300.f)
	{
		if (PathIndex < Path.Num() - 1)
			return true;
	}
	return false;
}

void UMolochStateMachine::MoveToTarget(FVector Target, const float MovementSpeed, const float DeltaTime,
                                       const float RotationSpeed, bool IgnoreAllCol, bool IgnorePawns) const
{
	// Target = SelfRef->GetActorLocation() - Target;
	FocusOnLocation(Target, DeltaTime, RotationSpeed);
	Target = Target - SelfRef->HeadLocation->GetComponentLocation();
	Target.Z = 0;
	SelfRef->MovementComponent->SetDirection(SelfRef->GetActorForwardVector(), MovementSpeed, IgnoreAllCol,
	                                         IgnorePawns);
}

void UMolochStateMachine::FocusOnLocation(FVector Location, float DeltaTime, float RotationSpeed) const
{
	FVector Target = Location - SelfRef->HeadLocation->GetComponentLocation();
	Target.Normalize();
	const FRotator LookAtRotation(
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, RotationSpeed).Rotation());
	const FRotator ZeroedRotation = FRotator(0.f, LookAtRotation.Yaw, 0.f);
	SelfRef->SetActorRotation(ZeroedRotation);
}

float UMolochStateMachine::CalculateAngleBetweenVectors(FVector VectorOne, FVector VectorTwo) const
{
	VectorOne.Normalize();
	VectorTwo.Normalize();

	const float DotProduct = FVector::DotProduct(VectorOne, VectorTwo);

	const float Angle = FMath::Acos(DotProduct);
	const float AngleInDegree = FMath::RadiansToDegrees(Angle);

	return AngleInDegree;
}

AMolochPawn* UMolochStateMachine::GetSelfRef() const
{
	if (!SelfRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Self Ref in Deprived StateMachine"))
	}
	return SelfRef;
}

APlayerCharacter* UMolochStateMachine::GetPlayer() const
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player in Deprived StateMachine"))
	}
	return Player;
}
