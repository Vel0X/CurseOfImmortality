// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneWhisper.h"
#include "NiagaraComponent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

static TArray<AActor*> HitActors;
static FVector SpawnLocation = FVector::ZeroVector;

AArcaneWhisper::AArcaneWhisper()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("Vfx");
	ParticleSystem->SetupAttachment(RootComponent);
}

void AArcaneWhisper::BeginPlay()
{
	Super::BeginPlay();
}

void AArcaneWhisper::InitializeAbility(ABaseCharacter* _Caster, int Level, const UAbilitySpecification* Specification)
{
	Super::InitializeAbility(_Caster, Level, Specification);
	HitActors.Empty();
	SpawnLocation = FVector::ZeroVector;
	DestroyOnEnemyHit = false;
}



void AArcaneWhisper::OnAbilityCreation()
{
	Super::OnAbilityCreation();
	
	if(SpawnLocation != FVector::ZeroVector)
		SetActorLocation(SpawnLocation);
	
	SetActorRotation(FRotator::ZeroRotator);
	Target = nullptr;
	
	TArray<ABaseCharacter*> Enemies = FPersistentWorldManager::GetEnemies();

	int ClosestIndex = -1;
	float ClosestDistance = 1000000.0f;
	const FVector ActorLocation = GetActorLocation();
	for (int i = 0; i < Enemies.Num(); ++i)
	{
		if(!Enemies[i])
		{
			UE_LOG(LogTemp, Warning, TEXT("ENEMY WAS NULL"));
			continue;
		}
		
		if(HitActors.Contains(Enemies[i]))
			continue;
		
		const float Distance = FVector::Distance(Enemies[i]->GetActorLocation(), ActorLocation);

		if(Distance > BounceRange)
			continue;
		
		if(Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestIndex = i;
		}
	}

	if(ClosestIndex != -1)
	{
		Target = Enemies[ClosestIndex];
		HitActors.Add(Target);
	}

	SpawnLocation = FVector::Zero();
	DelayedInitPending = true;
}



void AArcaneWhisper::AfterInitialization()
{
	Super::AfterInitialization();
}

void AArcaneWhisper::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	//Hit the Target in the first active Tick. This needs to happen because the ability can not be destroyed on its creation.
	if(DelayedInitPending)
	{
		if(Target)
		{
			ParticleSystem->SetNiagaraVariableVec3("User.Target", Target->GetAttachmentLocation(CenterPoint)->GetComponentLocation());
			SpawnLocation = Target->GetAttachmentLocation(CenterPoint)->GetComponentLocation();
			DamageComponent->DirectCharacterHit(0, Target);
			OnCharacterHit(Target);
		}
		else
		{
			Destroy(); //regular Destroy, as the Ability basically has not even spawned yet
		}
		DelayedInitPending = false;
	}
}

