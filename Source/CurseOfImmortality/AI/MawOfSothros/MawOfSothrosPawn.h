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

	virtual void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	virtual void OnDeath() override;

	UFUNCTION(BlueprintCallable)
	void ActivateVomit();
	UFUNCTION(BlueprintCallable)
	void DeactivateVomit();
	UFUNCTION(BlueprintCallable)
	void ToggleArmDamage();
	UFUNCTION(BlueprintCallable)
	void ToggleHeadDamage();
	UFUNCTION(BlueprintCallable)
	void TriggerMawSlam(FName SocketName);
	UFUNCTION(BlueprintCallable)
	void ToggleLaser();
	UFUNCTION(BlueprintCallable)
	void TriggerTailSweep();

	virtual bool GetSpawnPosition(FVector& Position, FRotator& Rotation) override;

	UPROPERTY(EditDefaultsOnly)
	UAbilitySpecification* SeaOfDarknessSpecification;
	UPROPERTY(EditDefaultsOnly)
	UAbilitySpecification* LaserBeamSpecification;
	UPROPERTY(EditDefaultsOnly)
	UAbilitySpecification* MawSlamSpecification;
	UPROPERTY(EditDefaultsOnly)
	UAbilitySpecification* TailSweepSpecification;

	//Collisions
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* PuddleLowerSpawnLocation = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* PuddleUpperSpawnLocation = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* TailSweepLocation = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* UpperBodyCollision = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* UpperLeftArmCollision = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* LowerLeftArmCollision = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* UpperRightArmCollision = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* LowerRightArmCollision = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* HeadCollision = nullptr;

	//Damage
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SmokeDamageSphere = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCapsuleComponent* LeftArmDamageCapsule = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCapsuleComponent* RightArmDamageCapsule = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* HeadDamageSphere = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMawOfSothrosStateMachine* StateMachine = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* Mesh = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Beam = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator HeadRotation = FRotator::ZeroRotator;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* MawSmoke = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* VomitUpperJaw = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* VomitLowerJaw = nullptr;

	UPROPERTY(EditAnywhere)
	float AttackCooldown = 0.5f;
	float CurrentAttackCooldown = 0.f;

	//Stats
	UPROPERTY(EditAnywhere, Category="ChargeAttack")
	float ChargeAttackTurnSpeed = 20.f;
	UPROPERTY(EditAnywhere, Category="ChargeAttack")
	float ChargeAttackMovementSpeed = 1500.f;
	UPROPERTY(EditAnywhere, Category="Idle")
	float DistRangedAttack = 1400.f;
	UPROPERTY(EditAnywhere, Category="Idle")
	float DistMeleeAttack = 700.f;
	
	//States
	UPROPERTY(BlueprintReadWrite)
	bool Start = false;
	UPROPERTY(BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(BlueprintReadWrite)
	bool Vomit = false;
	UPROPERTY(BlueprintReadWrite)
	bool TailSweep = false;
	UPROPERTY(BlueprintReadWrite)
	bool ChargeAttack = false;
	UPROPERTY(BlueprintReadWrite)
	bool GroundSlam = false;
	UPROPERTY(BlueprintReadWrite)
	bool Laser = false;
	UPROPERTY(BlueprintReadWrite)
	bool AnimationEnd = false;

	UPROPERTY(BlueprintReadWrite)
	bool AnimationStart;

	bool SpawnPuddle;
	bool LaserOn;
};
