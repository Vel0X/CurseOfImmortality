// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Moloch/States/MolochChargeAttack.h"

#include "CurseOfImmortality/AI/Moloch/MolochPawn.h"
#include "CurseOfImmortality/AI/Moloch/MolochStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UMolochChargeAttack::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMolochStateMachine>(StateMachine);

	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->ChargedAttack = true;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("ChargedAttack State Entered"))
	}
}

void UMolochChargeAttack::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->ChargedAttack = false;
	if (FPersistentWorldManager::GetLogLevel(MolochStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("ChargedAttack State Exit"))
	}
}

void UMolochChargeAttack::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	FVector PlayerLocation = Player->GetActorLocation();
	FVector OwnLocation = SelfRef->HeadLocation->GetComponentLocation();
	PlayerLocation.Z = 0;
	OwnLocation.Z = 0;

	// UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::Dist(PlayerLocation, OwnLocation))

	DrawDebugLine(SelfRef->GetWorld(), PlayerLocation, OwnLocation, FColor::Red);
	if (FVector::Dist(PlayerLocation, OwnLocation) <= 100.f)
	{
		Controller->Transition(Controller->HitPlayer, Controller);
	}

	OwnLocation.Z = 100;
	FVector Target(OwnLocation + SelfRef->GetActorForwardVector() * 100.f);
	FVector LeftStart(OwnLocation + SelfRef->GetActorRightVector() * 100.f);
	FVector LeftEnd(LeftStart + SelfRef->GetActorForwardVector() * 100.f);
	FVector RightStart(OwnLocation + SelfRef->GetActorRightVector().operator-() * 100.f);
	FVector RightEnd(RightStart + SelfRef->GetActorForwardVector() * 100.f);

	FHitResult Hit;
	FHitResult HitLeft;
	FHitResult HitRight;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	CollisionParams.AddIgnoredActor(SelfRef);

	SelfRef->GetWorld()->LineTraceSingleByChannel(Hit, OwnLocation, Target, ECC_GameTraceChannel11, CollisionParams);
	SelfRef->GetWorld()->LineTraceSingleByChannel(HitLeft, LeftStart, LeftEnd, ECC_GameTraceChannel11, CollisionParams);
	SelfRef->GetWorld()->LineTraceSingleByChannel(HitRight, RightStart, RightEnd, ECC_GameTraceChannel11,
	                                              CollisionParams);

	DrawDebugLine(SelfRef->GetWorld(), OwnLocation, Target, FColor::Purple);
	DrawDebugLine(SelfRef->GetWorld(), LeftStart, LeftEnd, FColor::Purple);
	DrawDebugLine(SelfRef->GetWorld(), RightStart, RightEnd, FColor::Purple);

	if (Hit.bBlockingHit || HitLeft.bBlockingHit || HitRight.bBlockingHit)
	{
		Controller->Transition(Controller->HitWall, Controller);
	}
	Controller->MoveToTarget(Player->GetActorLocation(), 1200.f, DeltaTime, 180.f, false, true);
}
