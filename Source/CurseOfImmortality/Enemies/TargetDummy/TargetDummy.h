// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "TargetDummy.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ATargetDummy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ATargetDummy();


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	FVector P1;

	UPROPERTY(EditAnywhere)
	FVector P2;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	bool Current = false;
	FVector CurrentTarget;
};
