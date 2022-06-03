// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneReplicatorCrab.h"


// Sets default values
AArcaneReplicatorCrab::AArcaneReplicatorCrab()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void AArcaneReplicatorCrab::Initialize(FVector Direction, float Lifetime)
{
	SetActorRotation(Direction.Rotation());
	RemainingLifetime = Lifetime;
}

void AArcaneReplicatorCrab::OnDeath()
{
	Super::OnDeath();
}

// Called when the game starts or when spawned
void AArcaneReplicatorCrab::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AArcaneReplicatorCrab::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector Offset = DeltaTime * 100.0f * Speed * GetActorForwardVector();
	AddActorWorldOffset(Offset, false);

	RemainingLifetime -= DeltaTime;
	if(RemainingLifetime <= 0.0f)
	{
		OnDeath();
		Destroy();
	}
}

