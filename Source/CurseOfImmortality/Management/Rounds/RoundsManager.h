// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Round.h"
#include "GameFramework/Actor.h"
#include "RoundsManager.generated.h"

/**
 * Manages the GameFlow
 *
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

	void Restart();
	
	/**
	 * Tick the ActiveRound and check wether its over or not. If it is and AutomaticRoundIncrement is active, try to start the next round
	 */	
	virtual void Tick(float DeltaTime) override;

	/**
	 * Try to start a round. The Index looks into an array specified in the Spawnables DataAsset, that holds all spawnable Objects
	 *
	 * Will be automatically used when a round is over and AutomaticRoundIncrement is active
	 * Can be manually called (maybe better, so the player can choose himself, when to start a new round)
	 */
	void StartRound(const int Index);

	int InitializationPending = 3;

	UFUNCTION(BlueprintCallable)
	void EndCurrentRound();
	
	/**
	 * Receive a Notification when an enemy died. Information will be passed on to the currently active round
	 */
	void OnEnemyDied(ABaseEnemyPawn* Enemy) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	URound* ActiveRound;

	int CurrentRoundIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoRoundIncrement = true;
};
