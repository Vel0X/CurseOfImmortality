// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/DolomarsWrath.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

ADolomarsWrath::ADolomarsWrath()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("Vfx");
	ParticleSystem->SetupAttachment(RootComponent);

	Collider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	Collider->SetupAttachment(RootComponent);
}

void ADolomarsWrath::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentScale = FMath::FInterpTo(CurrentScale, 1, DeltaSeconds, 5.f);
	FVector Scale(CurrentScale);
	RootComponent->SetWorldScale3D(Scale);

	if (Active)
	{
		Collider->SetGenerateOverlapEvents(false);
		DamageDuration -= DeltaSeconds;
	}
	if (Duration <= 0.f && !Active)
	{
		Collider->SetGenerateOverlapEvents(true);
		Active = true;
	}
	Duration -= DeltaSeconds;
}
