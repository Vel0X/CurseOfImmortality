// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"
#include "MawOfSothrosPawn.generated.h"

class USphereComponent;
class UAbilitySpecification;
class UMawOfSothrosStateMachine;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AMawOfSothrosPawn : public ABaseEnemyPawn
{
	GENERATED_BODY()
public:
	AMawOfSothrosPawn();

	void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void ActivateVomit();
	UFUNCTION(BlueprintCallable)
	void DeactivateVomit();
	UFUNCTION(BlueprintCallable)
	void ToggleArmDamage();
	UFUNCTION(BlueprintCallable)
	void ToggleHeadDamage();

	//AbilityTrigger
	UFUNCTION(BlueprintCallable)
	void TriggerMawSlam(FName SocketName);
	UFUNCTION(BlueprintCallable)
	void ToggleLaser();
	UFUNCTION(BlueprintCallable)
	void TriggerTailSweep();

	//States
	UPROPERTY(BlueprintReadWrite)
	bool Start;
	UPROPERTY(BlueprintReadWrite)
	bool Idle;
	UPROPERTY(BlueprintReadWrite)
	bool Vomit;
	UPROPERTY(BlueprintReadWrite)
	bool TailSweep;
	UPROPERTY(BlueprintReadWrite)
	bool ChargeAttack;
	UPROPERTY(BlueprintReadWrite)
	bool GroundSlam;
	UPROPERTY(BlueprintReadWrite)
	bool Laser;
	UPROPERTY(BlueprintReadWrite)
	bool AnimationEnd;

	UPROPERTY(EditDefaultsOnly)
	UAbilitySpecification* SeaOfDarknessSpecification;
	UPROPERTY(EditDefaultsOnly)
	UAbilitySpecification* LaserBeamSpecification;
	UPROPERTY(EditDefaultsOnly)
	UAbilitySpecification* MawSlamSpecification;
	UPROPERTY(EditDefaultsOnly)
	UAbilitySpecification* TailSweepSpecification;

	UPROPERTY(EditAnywhere)
	float AttackCooldown = 2.f;
	float CurrentAttackCooldown;

	bool SpawnPuddle;
	bool LaserOn;

	UPROPERTY(BlueprintReadWrite)
	bool AnimationStart; 

	//Stats
	UPROPERTY(EditAnywhere, Category="ChargeAttack")
	float ChargeAttackTurnSpeed = 20.f;
	UPROPERTY(EditAnywhere, Category="ChargeAttack")
	float ChargeAttackMovementSpeed = 1500.f;
	UPROPERTY(EditAnywhere, Category="Idle")
	float DistRangedAttack = 1400.f;
	UPROPERTY(EditAnywhere, Category="Idle")
	float DistMeleeAttack = 700.f;

	//Collisions
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* PuddleLowerSpawnLocation;
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* PuddleUpperSpawnLocation;
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* TailSweepLocation;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* UpperBodyCollision;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* UpperLeftArmCollision;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* LowerLeftArmCollision;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* UpperRightArmCollision;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* LowerRightArmCollision;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* HeadCollision;

	//Damage
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SmokeDamageSphere;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCapsuleComponent* LeftArmDamageCapsule;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCapsuleComponent* RightArmDamageCapsule;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* HeadDamageSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMawOfSothrosStateMachine* StateMachine;
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Beam;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator HeadRotation;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* MawSmoke;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* VomitUpperJaw;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* VomitLowerJaw;
};
