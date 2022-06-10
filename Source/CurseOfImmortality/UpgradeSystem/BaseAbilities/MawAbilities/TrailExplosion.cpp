// Fill out your copyright notice in the Description page of Project Settings.


#include "TrailExplosion.h"

#include "NiagaraComponent.h"


ATrailExplosion::ATrailExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("Vfx");
	ParticleSystem->SetupAttachment(RootComponent);
}

void ATrailExplosion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATrailExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

