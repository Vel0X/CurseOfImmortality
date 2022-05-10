// Fill out your copyright notice in the Description page of Project Settings.


#include "Fireball.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

AFireball::AFireball()
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

void AFireball::OnInteraction(ABaseAbility* OtherAbility)
{
	Super::OnInteraction(OtherAbility);
	UE_LOG(LogTemp, Warning, TEXT("ffff"));
	//rotate the Actor 180°
	FVector NewForward = GetActorForwardVector();
	NewForward.X *= -1;
	NewForward.Y *= -1;

	SetActorRotation(NewForward.Rotation());
	
}

void AFireball::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const FVector DeltaLocation = GetActorForwardVector() * Speed * DeltaSeconds * 100.0f;
	AddActorWorldOffset(DeltaLocation, false);
}
