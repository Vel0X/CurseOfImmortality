// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapComponent.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "BaseTrap.generated.h"

class UAbilitySpecification;
UCLASS()
class CURSEOFIMMORTALITY_API ABaseTrap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializeTrap();
	void CheckCollisions();

	UFUNCTION(BlueprintImplementableEvent)
	void DisableTrap();
	UFUNCTION(BlueprintImplementableEvent)
	void EnableTrap();
	UFUNCTION(BlueprintCallable)
	void FireProjectile(FVector SpawnLocation, FRotator SpawnRotation);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDamageComponent* DamageComponent = nullptr;
	UPROPERTY(EditAnywhere)
	TArray<UPrimitiveComponent*> HitBoxes;

	bool CanInteract = false;

private:
	UPROPERTY(EditAnywhere)
	TArray<ABaseCharacter*> InitialCollisions;
};
