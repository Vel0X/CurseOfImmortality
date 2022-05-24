// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Round.h"
#include "GameFramework/Actor.h"
#include "RoundsManager.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API ARoundsManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoundsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartRound(const int Index);

	void OnEnemyDied(ABaseEnemyPawn* Enemy);

	UPROPERTY(EditAnywhere)
	URound* ActiveRound;
};
