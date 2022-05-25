// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Round.h"
#include "GameFramework/Actor.h"
#include "RoundsManager.generated.h"

/**
 * Manages the flow of the Rounds and the rounds themselves
 *
 */
UCLASS()
class CURSEOFIMMORTALITY_API ARoundsManager : public AActor
{
	GENERATED_BODY()

public:
	ARoundsManager();

protected:
	virtual void PostInitializeComponents() override;

	/**
	 * If AutomaticRoundIncrement is active, immediately start a round
	 */
	virtual void BeginPlay() override;
	

public:
	/**
	 * Tick the ActiveRound and check wether its over or not. If it is and AutomaticRoundIncrement is active, try to start the next round
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * Try to start a round. The Index looks into an array specified in the Spawnables DataAsset, that holds all spawnable Objects
	 */
	void StartRound(const int Index);

	/**
	 * Receive a Notification when an enemy died. Information will be passed on to the currently active round
	 */
	void OnEnemyDied(ABaseEnemyPawn* Enemy) const;

	UPROPERTY(EditAnywhere)
	URound* ActiveRound;

	int CurrentRoundIndex = 0;
};
