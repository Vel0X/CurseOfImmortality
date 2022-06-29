// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/BaseClasses/DestructibleObject.h"
#include "CurseOfImmortality/Traps/BaseTrap.h"
#include "GameFramework/Actor.h"
#include "Arena.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API AArena : public AActor
{
	GENERATED_BODY()

public:
	AArena();
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	void DisableAllObstacles();

	USceneComponent* GetRandomGate() const;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* Gate1;

	UPROPERTY(EditAnywhere)
	USceneComponent* Gate2;

	UPROPERTY(EditAnywhere)
	USceneComponent* Gate3;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* Gate4;

	UPROPERTY(EditAnywhere)
	USceneComponent* LargeGate;

	UPROPERTY(EditAnywhere)
	USceneComponent* ChaliceLocation;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* PlayerSpawnPosition;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* MawSpawnPosition;

	UPROPERTY(EditAnywhere)
	TArray<ADestructibleObject*> DestructibleObjects;

	UPROPERTY(EditAnywhere)
	TArray<ABaseTrap*> Traps;
};
