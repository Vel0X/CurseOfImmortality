// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/MawSlam.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

AMawSlam::AMawSlam()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("Vfx");
	ParticleSystem->SetupAttachment(RootComponent);

	Collider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	Collider->SetupAttachment(RootComponent);
}

void AMawSlam::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (DamageWindow <= 0.f)
	{
		Collider->SetGenerateOverlapEvents(false);
	}
	DamageWindow -= DeltaSeconds;
}