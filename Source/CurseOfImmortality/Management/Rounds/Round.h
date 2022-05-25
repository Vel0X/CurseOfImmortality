// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "UObject/Object.h"
#include "Round.generated.h"

class ABaseCharacter;
class UAssortmentSpecification;
class URoundSpecification;
/**
 * Each Round consists out of a number of single enemies, as well as a number of predefined assortments of enemies. Each Enemy has a powerlevel assigned to it.
 * Each Round has a predefined powerlevel
 * Each Round can also have multiple stages, which have a powerlevel and time threshhold when they will be initiated.
 *
 * Enemies will be spawned at the beginning of each stage. The amount is determined using (TotalPowerLevelOfTheRound / Stages). SpawnPositions of the enemies are
 * determined using the enemies specific spawn behaviour. Each assortment can also spawn its enemies in a specific way. 
 */
UCLASS()
class CURSEOFIMMORTALITY_API URound : public UObject
{
	GENERATED_BODY()

public:

	/**
	 * make the Specification a member of the round (NOTE: Maybe just copy all the fields into separate member variables, in order to not risk violating the Data Asset?)
	 */
	void SetupRound(URoundSpecification* _Specification);

	/**
	 * Resolve all the Weighted probabilities contained in the RoundSpecification and determine how many enemies and assortments of which type to spawn
	 * If successful, the round is then properly started and enemies are spawned.
	 */
	void BeginRound();

	/**
	 * Track the state of the current round. Transition into the next stage or end the round if conditions are met
	 */
	void RoundTick(float DeltaTime);

	/**
	 * Spawn enemies. The Spawn process is random at the moment, meaning that it can not be specified which enemies to spawn at which stage.
	 * The amount of enemies to spawn per stage is determined using a fraction of the total PowerLevel of the round (TotalPowerLevel / Stages)
	 */
	void SpawnEnemies();

	/**
	 * Cleanup the round after it is over, removing all the dead enemies.
	 * If the player died during the round, the active enemies will also be deleted
	 */
	void EndRound();

	/**
	 * Notification that an enemy was defeated. If it belonged to round, remove the enemy from it. Necessary to determine when the round is over
	 */
	void OnEnemyDeath(ABaseEnemyPawn* Enemy);
		
	/**
	 * Sum up the powerlevel of all the currently active powerlevel
	 */
	int CalculateRemainingPowerLevel();

	UPROPERTY(EditAnywhere)
	URoundSpecification* Specification;

	UPROPERTY(EditAnywhere)
	TArray<UAssortmentSpecification*> RemainingAssortments;
	UPROPERTY(EditAnywhere)
	TArray<ABaseEnemyPawn*> ActiveEnemies;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EAssortment>, int> AssortmentsToSpawn;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EEnemy>, int> EnemiesToSpawn;

	int RoundPowerLevel = 0;
	int CurrentStage = 0;
	float StageTime = 0.0f;

	/**
	 * Are there still pending spawns in the round or are all spawned?
	 */
	bool SpawnsRemaining = false;

	/**
	 * Will be set false, once all enemies are defeated
	 */
	bool RoundOngoing = false;
};

