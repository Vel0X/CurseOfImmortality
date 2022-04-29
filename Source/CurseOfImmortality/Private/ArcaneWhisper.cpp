// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneWhisper.h"

#include "GameController.h"
#include "NiagaraComponent.h"
#include "../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/fmt/bundled/format.h"

void AArcaneWhisper::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorRotation(FRotator::ZeroRotator);
	Target = nullptr;
	
	TArray<AActor*> Enemies = static_cast<UGameController*>(GetGameInstance())->GetEnemies();
	UE_LOG(LogTemp, Warning, TEXT("HIT %d"), HitActors.Num());

	int ClosestIndex = -1;
	float ClosestDistance = 1000000.0f;
	for (int i = 0; i < Enemies.Num(); ++i)
	{
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
		HitActors.Add(Target);
	}

}

void AArcaneWhisper::AfterInitialization()
{
	Super::AfterInitialization();
	UE_LOG(LogTemp, Warning, TEXT("AFTER INIT"));

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
		OnEnemyHit(this, Target);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DESTROY"));
		Destroy(); //regular Destroy, as the Ability basically has not even spawned yet
	}
}

void AArcaneWhisper::AbilityCreationCallback(ABaseAbility* Caller)
{
	Super::AbilityCreationCallback(Caller);
	AArcaneWhisper* P = static_cast<AArcaneWhisper*>(Caller);
	P->HitActors.Add(Target);
	SetActorLocation(P->Target->GetActorLocation());
	GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Hello %s"),*GetActorLocation().ToString()));

}
