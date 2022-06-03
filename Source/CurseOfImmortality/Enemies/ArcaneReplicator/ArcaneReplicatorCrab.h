// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "GameFramework/Actor.h"
#include "ArcaneReplicatorCrab.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API AArcaneReplicatorCrab : public ABaseEnemyPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArcaneReplicatorCrab();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	float Speed = 5.0f;
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//UStormCallerStateMachine* StateMachine;

	void Initialize(FVector Direction, float Lifetime);

	float RemainingLifetime = 1.0f;

	virtual void OnDeath() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
