// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Inu/InuStateMachine.h"

#include "InuPawn.h"
#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/Utility/DetachedParticleActor.h"
#include "States/InuFindStartLocation.h"
#include "States/InuIdleState.h"
#include "States/InuRangedAttack.h"
#include "States/InuRunningState.h"
#include "States/InuRetreatState.h"

void UInuStateMachine::BeginPlay()
{
	Super::BeginPlay();

	//Initialise References
	SelfRef = Cast<AInuPawn>(GetOwner());

	//Initialise States
	Idle = NewObject<UInuIdleState>();
	RangedAttack = NewObject<UInuRangedAttack>();
	Running = NewObject<UInuRunningState>();
	FindStartLocation = NewObject<UInuFindStartLocation>();
	Retreat = NewObject<UInuRetreatState>();
}

void UInuStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Player)
	{
		Player = FPersistentWorldManager::PlayerCharacter;
		CurrentState = FindStartLocation;
		CurrentState->OnStateEnter(this);
	}
	if (!SelfRef->Dead)
	{
		CurrentState->OnStateUpdate(DeltaTime);
		SelfRef->CurrentAttackCoolDown -= DeltaTime;
	}
	else
	{
		auto Actor = GetWorld()->SpawnActor<ADetachedParticleActor>();
		Actor->InitializeParticleActor(SelfRef->CenterAttachmentPoint->GetComponentLocation(), SelfRef->DeathParticle);
		SelfRef->Destroy();
	}
}

AInuPawn* UInuStateMachine::GetSelfRef() const
{
	if (!SelfRef) { return nullptr; }
	return SelfRef;
}

ABaseCharacter* UInuStateMachine::GetPlayer() const
{
	if (!Player) { return nullptr; }
	return Player;
}

void UInuStateMachine::FocusOnPlayer(float DeltaTime) const
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in StormCaller StateMachine")); }
	if (!Player) { UE_LOG(LogTemp, Error, TEXT("No Player in StormCaller StateMachine")); }
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	const FRotator LookAtRotation(
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, 180.f).Rotation());
	SelfRef->SetActorRotation(LookAtRotation);
}

bool UInuStateMachine::CheckLineOfSight(FVector Target) const
{
	FVector Start(SelfRef->GetActorLocation());
	Start.Z = 20;
	Target.Z = 20;

	FHitResult Hit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	CollisionParams.AddIgnoredActor(SelfRef);

	// DrawDebugLine(GetWorld(), LeftStart, LeftEnd, FColor::Red);

	GetWorld()->LineTraceSingleByChannel(Hit, Start, Target, ECC_GameTraceChannel3, CollisionParams);

	return Hit.bBlockingHit;
}


void UInuStateMachine::FindPathToPlayer(TArray<FVector>& Path) const
{
	Path.Empty();
	APathfindingGrid* Grid = FPersistentWorldManager::PathfindingGrid;
	if (!Grid)
	{
		UE_LOG(LogTemp, Error, TEXT("No Grid in Inu State Machine"));
		return;
	}

	if (!Grid->GetPathWorldSpace(SelfRef->GetActorLocation(), Player->GetActorLocation(), Path, false))
	{
		Path.Empty();
		UE_LOG(LogTemp, Error, TEXT("Path is Missing"));
	}
}

void UInuStateMachine::FindRandomPath(TArray<FVector>& Path, FVector& RandomLocation) const
{
	Path.Empty();
	APathfindingGrid* Grid = FPersistentWorldManager::PathfindingGrid;
	if (!Grid)
	{
		UE_LOG(LogTemp, Error, TEXT("No Grid in Inu State Machine"));
		return;
	}

	const FPfNode* EndNode = Grid->GetRandomNodeInNavMesh();

	if (EndNode->IsWalkable && !EndNode->SpawnArea)
	{
		Grid->GetWorldPositionFromCoordinates(EndNode->X, EndNode->Y, RandomLocation);

		if (!Grid->GetPathWorldSpace(SelfRef->GetActorLocation(), RandomLocation, Path, false))
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

bool UInuStateMachine::FollowPath(TArray<FVector> Path, float DeltaTime, int PathIndex, float RotationSpeed,
                                  float CurveValue) const
{
	FVector L(SelfRef->GetActorLocation());
	L.Z = 0;

	MoveToTarget(Path[PathIndex], SelfRef->Stats[Movespeed] * CurveValue, DeltaTime, RotationSpeed);

	if (FVector::Dist(Path[PathIndex], L) < 100.f)
	{
		if (PathIndex < Path.Num() - 1)
			return true;
	}

	return false;
}

void UInuStateMachine::MoveToTarget(FVector Target, const float MovementSpeed, const float DeltaTime,
                                    const float RotationSpeed) const
{
	// Target = SelfRef->GetActorLocation() - Target;
	FocusOnLocation(Target, DeltaTime, RotationSpeed);
	Target = Target - SelfRef->GetActorLocation();
	Target.Z = 0;
	if (SelfRef->StartGatePassed)
	{
		SelfRef->MovementComponent->SetDirection(SelfRef->GetActorForwardVector(), MovementSpeed, false, false);
	}
	else
	{
		SelfRef->MovementComponent->SetDirection(SelfRef->GetActorForwardVector(), MovementSpeed, true, false);
	}
}

void UInuStateMachine::FocusOnLocation(const FVector Location, const float DeltaTime,
                                       const float RotationSpeed) const
{
	FVector Target = Location - SelfRef->GetActorLocation();
	Target.Normalize();
	const FRotator LookAtRotation(
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, RotationSpeed).Rotation());
	const FRotator ZeroedRotation = FRotator(0.f, LookAtRotation.Yaw, 0.f);
	SelfRef->SetActorRotation(ZeroedRotation);
}
