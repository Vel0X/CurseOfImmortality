// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageIndicator.generated.h"

class UTextRenderComponent;
UCLASS()
class CURSEOFIMMORTALITY_API ADamageIndicator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageIndicator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetText(FString Text) const;
	
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* TextComponent;

	UPROPERTY(EditAnywhere)
	float LifeTime = 0.5f;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere)
	UCurveFloat* SpeedOverTime;
	
	UPROPERTY(EditAnywhere)
	FVector MoveDirection;

private:
	float RemainingLifetime = 0.0f;
};



