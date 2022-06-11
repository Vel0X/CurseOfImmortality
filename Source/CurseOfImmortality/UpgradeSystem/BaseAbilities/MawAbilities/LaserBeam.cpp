// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBeam.h"

#include "NiagaraComponent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/Utility/DetachedParticleActor.h"


// Sets default values
ALaserBeam::ALaserBeam()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("Vfx");
	ParticleSystem->SetupAttachment(RootComponent);
}

void ALaserBeam::BeginPlay()
{
	Super::BeginPlay();
	Handle = FMath::Rand();
	//PositionLastFrame = GetActorLocation();
}

void ALaserBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TimeUntilNextSpawn <= 0.0f)
	{
		TimeUntilNextSpawn = SpawnInterval;
		const auto AbilityInstance = FPersistentWorldManager::ObjectFactory->SpawnAbility(TrailExplosion, GetActorLocation(), GetActorRotation(), Caster);
		AbilityInstance->AbilityHandle = Handle;
	}
	TimeUntilNextSpawn -= DeltaTime;

	/*
	const FVector PositionThisFrame = GetActorLocation();
	const float DistanceThisFrame = FVector::Distance(PositionLastFrame, PositionThisFrame);
	CurrentLength += DistanceThisFrame;
	DistanceBuffer.Add(DistanceThisFrame);
	CurrentLifetime += DeltaTime;
	/*
	if(CurrentLifetime > 3.0f)
	{
		const float DistanceToSubtract = DistanceBuffer[0];
		DistanceBuffer.RemoveAt(0);
		CurrentLength -= DistanceToSubtract;
	}
	
	ParticleSystem->SetFloatParameter("User.Tiling", CurrentLength);
	ParticleSystem->SetFloatParameter("User.RemainingLifeTime", RemainingAbilityLifetime);
	//UE_LOG(LogTemp, Warning, TEXT("Length %f"), CurrentLength);
	
	PositionLastFrame = PositionThisFrame;
	*/
}

void ALaserBeam::DestroyAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("???"));
	const auto DetachedParticleActor = GetWorld()->SpawnActor<ADetachedParticleActor>();
	DetachedParticleActor->InitializeParticleActor(ParticleSystem, this, -1);
	Super::DestroyAbility();
}

