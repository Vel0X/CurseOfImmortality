// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/DamageSpecification.h"
#include "GameFramework/Pawn.h"
#include "BaseCharacter.generated.h"

class UDamageComponent;
class UCapsuleComponent;
class UBaseStatSpecification;
class UNiagaraSystem;
class UNiagaraComponent;
class ABaseAbility;
class UBaseBuff;
class UCharacterMovement;

USTRUCT()
struct FDamageReceiverHandle
{
	GENERATED_BODY()

	FDamageReceiverHandle() : Handle(-1), Expiration(0.0f){}

	FDamageReceiverHandle(int Handle, float Expiration): Handle(Handle), Expiration(Expiration){}

	int Handle;
	float Expiration;
};



UCLASS()
class CURSEOFIMMORTALITY_API ABaseCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseCharacter();

	virtual ~ABaseCharacter() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckCollisions();
	void UpdateDamageReceiverHandles(float DeltaTime);

	bool DamageReceiverHandleContained(int Handle);
	
	virtual void Setup();
	
	virtual void OnDeath();

	UPROPERTY(EditAnywhere)
	UCharacterMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDamageComponent* DamageComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current")
	float CurrentMovementSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	bool Immune;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	bool Dead;

	
	/**
	 * @brief Recalculate the Stats of the Char, by getting the BaseStats and adding all the Stat Modifications on top
	 */
	void RecalculateStats();

	void AddBuff(UBaseBuff* Buff, ABaseCharacter* Inflicter, int Level);
	void RemoveBuff(UBaseBuff* Buff);

	/**
	 * @brief Generic function for receiving damage
	 * @param Amount How much Damage was done
	 * @param Dealer Who dealt the Damage
	 * @param Ability By which Ability was the Damage dealt (null, if the Damage was done some other way)
	 * @param Visual Enable Damage Numbers
	 */
	void TakeDmg(float Amount, ABaseCharacter* Dealer, ABaseAbility* Ability, bool Visual = true);

	void TakeDmg(FDamageFormula Formula, ABaseCharacter* Dealer, ABaseAbility* Ability, bool Visual = true);

	void OnDamageDealt(float Amount, ABaseCharacter* DamageRecipient);
	
	void Heal(float Amount, bool Verbose = false);
	
	UNiagaraComponent* SetupBuffVfx(UNiagaraSystem* Vfx, const EAttachmentPoint AttachmentPoint, int& Handle);
	
	void RemoveBuffVfx(const int Handle, const bool SpawnDetachedParticleActor = true);

	USceneComponent* GetAttachmentLocation(EAttachmentPoint Point);
	
	UPROPERTY(EditAnywhere)
	TArray<UBaseBuff*> Buffs;

	UPROPERTY(EditAnywhere)
	TMap<int, UNiagaraComponent*> ActiveParticleEffects;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBaseStatSpecification* BaseStats;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* Blood; //for regular DamageObjects

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* LesserBlood; //for lingering DamageObjects (and Dot Effects)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<EStats>, float> Stats;

	UPROPERTY(EditAnywhere)
	FString DisplayName = "";

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EFaction> Faction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* UpperAttachmentPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* CenterAttachmentPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* LowerAttachmentPoint;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	//UPROPERTY(EditDefaultsOnly)
	//UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleCollision;
	
	UPROPERTY(EditAnywhere)
	TArray<UPrimitiveComponent*> BodyHitboxes;

	UPROPERTY(EditAnywhere)
	TArray<UPrimitiveComponent*> DamageHitboxes;

	//An Array containing Indizes of Abilities by which the player was already hit. This allows multiple abilities to be grouped with the same handle, thus avoiding the player being hit by them multiple times
	UPROPERTY(EditAnywhere)
	TArray<FDamageReceiverHandle> DamageReceiverHandles;
private:
	
	int ActiveParticleEffectHandle = 0;
};
