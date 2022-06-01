// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetDummy.h"

#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"

ATargetDummy::ATargetDummy() : ABaseCharacter()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void ATargetDummy::BeginPlay()
{
	Super::BeginPlay();

	CurrentTarget = P1;
}

void ATargetDummy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(Static)
		return;
	
	FVector CorrectedTarget = CurrentTarget;
	CorrectedTarget.Z = 0.0f;
	FVector CorrectedLocation = GetActorLocation();
	CorrectedLocation.Z = 0.0f;

	if(FVector::Dist(CorrectedTarget, CorrectedLocation) <= 10.0f)
	{
		Current = !Current;
		CurrentTarget = Current ? P2 : P1; 	
	}
	else
	{
		FVector Direction = CorrectedTarget - CorrectedLocation;
		Direction.Normalize();
		SetActorRotation(Direction.Rotation());
		MovementComponent->SetDirection(GetActorForwardVector(), Stats[EStats::Movespeed]);
	}
}
