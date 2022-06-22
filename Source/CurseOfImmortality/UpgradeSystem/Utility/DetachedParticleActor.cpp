// Fill out your copyright notice in the Description page of Project Settings.


#include "DetachedParticleActor.h"


// Sets default values
ADetachedParticleActor::ADetachedParticleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADetachedParticleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADetachedParticleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(RemainingLifetime <= 0.0f)
	{
		Destroy();
	}
	else
	{
		RemainingLifetime -= DeltaTime;
	}

	if(FollowParent != nullptr)
	{
		SetActorLocation(FollowParent->GetActorLocation());
	}
}
	
void ADetachedParticleActor::InitializeParticleActor(UNiagaraComponent* ParticleSystem,
	AActor* _FollowParent, float ManualDestructionTime)
{
	RemainingLifetime = ManualDestructionTime == -1 ? 5.0f : ManualDestructionTime;

	if(!ParticleSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Particlesystem was null when trying to attach to DetachedParticleActor"));
		return;
	}
	
	ParticleSystem->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	ParticleSystem->Deactivate();

	if(_FollowParent != nullptr)
	{
		FollowParent = _FollowParent;
	}
}

void ADetachedParticleActor::InitializeParticleActor(FVector SpawnLocation, UNiagaraSystem* ParticleSystem, AActor* _FollowParent,
	float ManualDestructionTime)
{
	RemainingLifetime = ManualDestructionTime == -1 ? 5.0f : ManualDestructionTime;


	SetActorLocation(SpawnLocation);
	if(!ParticleSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Particlesystem was null when trying to attach to DetachedParticleActor"));
		return;
	}
	UNiagaraComponent* NewComp = NewObject<UNiagaraComponent>(this);
	NewComp->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	NewComp->RegisterComponent();
	NewComp->SetAsset(ParticleSystem);
	NewComp->SetWorldLocation(SpawnLocation);
	NewComp->Activate();
	//Vfx->Deactivate();

	if(_FollowParent != nullptr)
	{
		FollowParent = _FollowParent;
	}
}

