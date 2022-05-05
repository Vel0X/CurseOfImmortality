// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Char.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "GameFramework/Actor.h"
#include "MainChar.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API AMainChar : public AChar
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMainChar();
	void BindToInput(); 
	void OnRangedKeyPressed();
	void OnSpecialKeyPressed();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	UPROPERTY(EditAnywhere)
	UAttackManager* AttackManager;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
};

