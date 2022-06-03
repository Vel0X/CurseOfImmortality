// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundManager.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API ASoundManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASoundManager();
	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlaySFX(const FString& Name);
	void PlaySoundAttached(const USceneComponent* Component, const FString& Name);
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PlaySFXImpl(const FString& Name);

	

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySoundAttachedImpl(const USceneComponent* Component, const FString& Name);

	UFUNCTION(BlueprintCallable)
	USoundWave* GetSound(FString Name);
};
