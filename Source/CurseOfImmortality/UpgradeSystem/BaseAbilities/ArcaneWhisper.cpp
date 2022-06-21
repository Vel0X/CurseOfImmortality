// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneWhisper.h"
#include "NiagaraComponent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

static TArray<AActor*> HitActors;

void AArcaneWhisper::BeginPlay()
{
	Super::BeginPlay();
}

void AArcaneWhisper::InitializeAbility(ABaseCharacter* _Caster, int Level, const UAbilitySpecification* Specification)
{
	Super::InitializeAbility(_Caster, Level, Specification);
	HitActors.Empty();
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
	for (int i = 0; i < Enemies.Num(); ++i)
	{
		if(Enemies[i] == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ENEMY WAS NULL"));
			continue;
		}
		
		if(HitActors.Contains(Enemies[i]))
			continue;
		
		const float Distance = FVector::Distance(Enemies[i]->GetActorLocation(), GetActorLocation());

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
		DamageComponent->DirectCharacterHit(0, Target);
		HitActors.Add(Target);
	}

	SpawnLocation = FVector::Zero();
}



void AArcaneWhisper::AfterInitialization()
{
	Super::AfterInitialization();
	bDelayedAfterInit = true;
}

void AArcaneWhisper::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);
	if(bDelayedAfterInit)
	{
		if(Target)
		{
			TArray<UNiagaraComponent*> NiagaraComponents;
			GetComponents<UNiagaraComponent>(NiagaraComponents);
			if(NiagaraComponents.Num() > 0)
			{
				NiagaraComponents[0]->SetNiagaraVariableVec3("User.Target", Target->GetAttachmentLocation(CenterPoint)->GetComponentLocation());
			}
			CanInteract = true;
			DestroyOnEnemyHit = false;
			SpawnLocation = Target->GetAttachmentLocation(CenterPoint)->GetComponentLocation();
			OnCharacterHit(Target);
		}
		else
		{
			Destroy(); //regular Destroy, as the Ability basically has not even spawned yet
		}
		bDelayedAfterInit = false;
	}
}

