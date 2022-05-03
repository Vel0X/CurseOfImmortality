// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CharacterMovement.h"
#include "BaseCharacter.generated.h"

class UCapsuleComponent;

UCLASS()
class CURSEOFIMMORTALITY_API ABaseCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Setup();

	virtual void ReceiveDamage(float Damage);

	virtual void DealDamage(float Damage, ABaseCharacter *EnemyCharacter);

	virtual void OnDeath();

	UPROPERTY(EditAnywhere)
	UCharacterMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	bool Died;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	bool Immune;
};
