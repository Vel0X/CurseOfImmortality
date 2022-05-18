// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneWhisper.h"
#include "NiagaraComponent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

static TArray<AActor*> HitActors;

void AArcaneWhisper::BeginPlay()
{
	Super::BeginPlay();
}

void AArcaneWhisper::InitializeAbility(int _AbilityHandle, ABaseCharacter* _Caster, int Level)
{
	Super::InitializeAbility(_AbilityHandle, _Caster, Level);
	HitActors.Empty();
}



void AArcaneWhisper::OnAbilityCreation()
{
	Super::OnAbilityCreation();
	//AArcaneWhisper* P = static_cast<AArcaneWhisper*>(Caller);
	//SetActorLocation(P->Target->GetActorLocation());
	//GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Hello %s"),*GetActorLocation().ToString()));

	if(SpawnLocation != FVector::ZeroVector)
	{
		SetActorLocation(SpawnLocation);
	}
	
	SetActorRotation(FRotator::ZeroRotator);
	Target = nullptr;
	
	TArray<ABaseCharacter*> Enemies = FPersistentWorldManager::GetEnemies(); //  static_cast<UGameController*>(GetGameInstance())->GetEnemies();
	//UE_LOG(LogTemp, Warning, TEXT("HIT %d"), HitActors.Num());

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
		//UE_LOG(LogTemp, Warning, TEXT("DIST %f"), Distance);
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
	UE_LOG(LogTemp, Warning, TEXT("AFTER INIT"));


}

void AArcaneWhisper::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);
	if(bDelayedAfterInit)
	{
		if(Target)
		{
			UE_LOG(LogTemp, Warning, TEXT("AFTER INIT SUCC"));

			TArray<UNiagaraComponent*> Chil;
			GetComponents<UNiagaraComponent>(Chil);
			//UE_LOG(LogTemp, Warning, TEXT("NUM %d"), Chil.Num());
			if(Chil.Num() > 0)
			{
				Chil[0]->SetNiagaraVariableVec3("User.Target", Target->GetActorLocation());
			}
			CanInteract = true;
			DestroyOnEnemyHit = false;
			SpawnLocation = Target->GetActorLocation();
			OnEnemyHit(this, Target);
		}
		else
		{
			Destroy(); //regular Destroy, as the Ability basically has not even spawned yet
		}
		bDelayedAfterInit = false;
	}
}

