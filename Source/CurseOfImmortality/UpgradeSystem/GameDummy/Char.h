// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Char.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API AChar : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//TArray<>
};
