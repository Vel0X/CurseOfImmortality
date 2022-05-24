// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "UObject/Object.h"
#include "Round.generated.h"

class ABaseCharacter;
class UAssortmentSpecification;
class URoundSpecification;
/**
 * Each Round consists out of a number of single enemies, as well as a number of predefined assortments of enemies. Each Enemy has a powerlevel assigned to it and each assortment has one.
 * Each Round has a predefined powerlevel
 * Each Round has stages, that also have powerlevels and timers.
 *
 *
 * Spawning Locations of Enemies:
 * For each enemy a spawning behaviour can be specified (Overriding GetSpawnPosition in your Enemy Class). In Object Factory there is a SpawnEnemy Overload, that uses this specification
 * Assortments can choose to spawn their Enemies directly without a SpawningBehaviour
 *
 * Assortments as their own classes?
 * - maybe a little overkill, but can be used later as a powerful tool to enable group behaviour of enemies
 */
UCLASS()
class CURSEOFIMMORTALITY_API URound : public UObject
{
	GENERATED_BODY()

public:
	void SetupRound(URoundSpecification* _Specification);
	void BeginRound(bool Verbose = false);
	void RoundTick(float DeltaTime);
	void EndRound();

	int CalculateRemainingPowerLevel();

	UPROPERTY(EditAnywhere)
	URoundSpecification* Specification;

	UPROPERTY(EditAnywhere)
	TArray<UAssortmentSpecification*> RemainingAssortments;
	UPROPERTY(EditAnywhere)
	TArray<ABaseCharacter*> ActiveEnemies;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EAssortment>, int> AssortmentsToSpawn;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EEnemy>, int> EnemiesToSpawn;

	int CurrentStage = 0;
	float StageTime = 0.0f;
};
