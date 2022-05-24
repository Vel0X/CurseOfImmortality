// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/StormCaller/StormCallerPawn.h"

#include "StormCallerStateMachine.h"
#include "Components/CapsuleComponent.h"
#include "CurseOfImmortality/AI/AIBaseClasses/RandomAOEAbilty.h"

AStormCallerPawn::AStormCallerPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	StateMachine = CreateDefaultSubobject<UStormCallerStateMachine>("StateMachine");

	StormCast = CreateDefaultSubobject<URandomAOEAbilty>("Storm Call");

	CurrentAttackCoolDown = AttackCoolDown;
}

void AStormCallerPawn::OnDeath()
{
	Super::OnDeath(); //Fix!!!
	Dead = true;
	StateMachine->DestroyComponent();
	CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

bool AStormCallerPawn::GetSpawnPosition(FVector& Position, FRotator& Rotation)
{
	const float X = FMath::FRandRange(-900.0f, 900.0f);
	const float Y = FMath::FRandRange(-900.0f, 900.0f);
	Position = FVector(X,Y, 100.0f);
	SetActorLocation(Position);
	return true;
}
