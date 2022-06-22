// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordSlash.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"


ASwordSlash::ASwordSlash()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail"));
	ParticleSystem->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
}

