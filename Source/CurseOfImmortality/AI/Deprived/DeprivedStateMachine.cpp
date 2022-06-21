// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "DeprivedPawn.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
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

UDeprivedStateMachine::UDeprivedStateMachine()
{
}

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
	SelfRef->CurrentJumpAttackCoolDown -= DeltaTime;
	SelfRef->CurrentFrenziedAttackCoolDown -= DeltaTime;
}

FHitResult UDeprivedStateMachine::CheckLineOfSight(FVector Target)
{
	FHitResult Hit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	CollisionParams.AddIgnoredActor(SelfRef);

	FVector Start = SelfRef->GetActorLocation();
	Start.Z += 20;
	FVector End = Target;
	End.Z += 20;

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel3, CollisionParams);

	return Hit;
}

void UDeprivedStateMachine::FindPathToPlayer(TArray<FVector>& Path) const
{
	Path.Empty();
	APathfindingGrid* Grid = FPersistentWorldManager::PathfindingGrid;

	if (!Grid->GetPathWorldSpace(SelfRef->GetActorLocation(), Player->GetActorLocation(), Path, false))
	{
		Path.Empty();
		UE_LOG(LogTemp, Error, TEXT("Path is Missing"));
	}
}

void UDeprivedStateMachine::FindRandomPath(TArray<FVector>& Path, FVector& RandomLocation) const
{
	Path.Empty();
	APathfindingGrid* Grid = FPersistentWorldManager::PathfindingGrid;

	FPfNode* EndNode = Grid->GetRandomNodeInNavMesh();

	if (EndNode->IsWalkable)
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

bool UDeprivedStateMachine::FollowPath(TArray<FVector> Path, float DeltaTime, int PathIndex) const
{
	FVector L(SelfRef->GetActorLocation());
	L.Z = 0;

	MoveToTarget(Path[PathIndex], SelfRef->Stats[Movespeed], DeltaTime, 180.f);

	if (FVector::Dist(Path[PathIndex], L) < 200.f)
	{
		if (PathIndex < Path.Num() - 1)
			return true;
	}

	return false;
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

void UDeprivedStateMachine::MoveToTarget(FVector Target, const float MovementSpeed, const float DeltaTime,
                                         const float RotationSpeed) const
{
	// Target = SelfRef->GetActorLocation() - Target;
	FocusOnLocation(Target, DeltaTime, RotationSpeed);
	Target = Target - SelfRef->GetActorLocation();
	Target.Z = 0;
	SelfRef->MovementComponent->SetDirection(SelfRef->GetActorForwardVector(), MovementSpeed, false);
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

float UDeprivedStateMachine::CalculateAngleBetweenVectors(FVector VectorOne, FVector VectorTwo) const
{
	VectorOne.Normalize();
	VectorTwo.Normalize();

	const float DotProduct = FVector::DotProduct(VectorOne, VectorTwo);

	const float Angle = FMath::Acos(DotProduct);
	float AngleInDegree = FMath::RadiansToDegrees(Angle);

	return AngleInDegree;
}
