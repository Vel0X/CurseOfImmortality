// Fill out your copyright notice in the Description page of Project Settings.


#include "Whirlwind.h"

#include "NiagaraComponent.h"

AWhirlwind::AWhirlwind()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Vfx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Vfx"));
	Vfx->SetupAttachment(RootComponent);
}
