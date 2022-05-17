// Fill out your copyright notice in the Description page of Project Settings.


#include "KarysAnimusProjectile.h"

#include "CurseOfImmortality/BaseClasses/GameController.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

AKarysAnimusProjectile::AKarysAnimusProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	Trail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail"));
	Trail->SetupAttachment(ProjectileMesh);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(ProjectileMesh);
}

void AKarysAnimusProjectile::BeginPlay()
{
	Super::BeginPlay();

	if(GetTarget())
	{
		//set spawn rotation
		const float X = FMath::RandRange(-SpawnAngleVariation, SpawnAngleVariation);
		const float Y = FMath::RandRange(-SpawnAngleVariation, SpawnAngleVariation);
		FVector Angle = FVector(X,Y,1);
		Angle.Normalize();
		const FRotator Rotation = UKismetMathLibrary::Conv_VectorToRotator(Angle);
		SetActorRotation(Rotation);
	}
	else
	{
		Destroy();
	}
}

void AKarysAnimusProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(Target == nullptr)
	{
		if(!GetTarget())
		{
			Destroy();
		}
		return;
	}
	FVector Direction = Target->GetActorLocation() - GetActorLocation();
	Direction.Normalize();
	//Direction * DeltaSeconds *

	const FVector NewDirection = FMath::VInterpNormalRotationTo(GetActorForwardVector(), Direction, DeltaSeconds, RotationSpeed);
	const FRotator Rotation = UKismetMathLibrary::Conv_VectorToRotator(NewDirection);
	SetActorRotation(Rotation);
	const FVector DeltaLocation = GetActorForwardVector() * Speed * DeltaSeconds * 100.0f;
	AddActorWorldOffset(DeltaLocation, false);
	
}

bool AKarysAnimusProjectile::GetTarget()
{
	TArray<AActor*> Enemies = static_cast<UGameController*>(GetGameInstance())->GetEnemies();
	int ClosestIndex = -1;
	float ClosestDistance = 1000000.0f;
	for (int i = 0; i < Enemies.Num(); ++i)
	{
		const float Distance = FVector::Distance(Enemies[i]->GetActorLocation(), GetActorLocation());
		if(Distance > MaxRange)
			continue;
		
		if(Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestIndex = i;
		}
	}

	if(ClosestIndex != -1)
	{
		Target = Enemies[ClosestIndex];
		return true;

	}
	return false;
}
