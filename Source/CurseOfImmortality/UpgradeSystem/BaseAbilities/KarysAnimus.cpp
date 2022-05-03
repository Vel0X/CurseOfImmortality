// Fill out your copyright notice in the Description page of Project Settings.


#include "KarysAnimus.h"


// Sets default values
AKarysAnimus::AKarysAnimus()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AKarysAnimus::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKarysAnimus::AnimatePosition(float DeltaTime)
{
	PassedTime += DeltaTime;
	const float Amplitude = FMath::Sin(PassedTime * 3.0f) * 1000.0f;
	const float Z = Amplitude - LastSineDelta;
	LastSineDelta = Amplitude;
	
	const FVector DeltaLocation = FVector(0,0,Z);
	const FRotator DeltaRotation = FRotator(0,DeltaTime * 30.0f,0);
	
	AddActorWorldOffset(DeltaLocation, false);
	AddActorLocalRotation(DeltaRotation, false);
}

// Called every frame
void AKarysAnimus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AnimatePosition(DeltaTime);
	
	if(TimeUntilNextSpawn <= 0.0f)
	{
		if(ProjectileClass != nullptr)
		{
			const FVector Location = GetActorLocation();
			AActor* Projectile = GetWorld()->SpawnActor(ProjectileClass, &Location);
		}
		
		TimeUntilNextSpawn = SpawnInterval;
	}
	else
	{
		TimeUntilNextSpawn -= DeltaTime;
	}
	
}

