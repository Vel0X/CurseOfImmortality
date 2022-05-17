// Fill out your copyright notice in the Description page of Project Settings.


#include "Whirlwind.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

AWhirlwind::AWhirlwind()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("Vfx");
	ParticleSystem->SetupAttachment(RootComponent);

	Collider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	Collider->SetupAttachment(RootComponent);
}

void AWhirlwind::BeginPlay()
{
	Super::BeginPlay();
}
