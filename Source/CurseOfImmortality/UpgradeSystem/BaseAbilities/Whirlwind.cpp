// Fill out your copyright notice in the Description page of Project Settings.


#include "Whirlwind.h"

#include "NiagaraComponent.h"

AWhirlwind::AWhirlwind()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("Vfx");
	ParticleSystem->SetupAttachment(RootComponent);

	DamageComponent = CreateDefaultSubobject<UDamageComponent>("DamageComponent");
}
