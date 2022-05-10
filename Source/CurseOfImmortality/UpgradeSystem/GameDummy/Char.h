// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "Char.generated.h"


class UNiagaraComponent;
class UNiagaraSystem;
class ABaseAbility;
class UBaseBuff;
class UBaseStatSpecification;
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

	/**
	 * @brief Recalculate the Stats of the Char, by getting the BaseStats and adding all the Stat Modifications on top
	 */
	void RecalculateStats();

	void AddBuff(UBaseBuff* Buff);
	void RemoveBuff(UBaseBuff* Buff);

	/**
	 * @brief Generic function for receiving damage
	 * @param Amount How much Damage was done
	 * @param Dealer Who dealt the Damage
	 * @param Ability By which Ability was the Damage dealt (null, if the Damage was done some other way)
	 * @param Verbose Enable Logging
	 */
	void TakeDmg(float Amount, AChar* Dealer, ABaseAbility* Ability, bool Verbose = false);
	
	void Heal(float Amount, bool Verbose = false);
	
	UNiagaraComponent* SetupBuffVfx(UNiagaraSystem* Vfx, const EAttachmentPoint AttachmentPoint, int& Handle);
	
	void RemoveBuffVfx(const int Handle, const bool SpawnDetachedParticleActor = true);

	UPROPERTY(EditAnywhere)
	TArray<UBaseBuff*> Buffs;

	UPROPERTY(EditAnywhere)
	TMap<int, UNiagaraComponent*> ActiveParticleEffects;
	
	float CurrentHealth = 0.0f;
	
	UPROPERTY(EditAnywhere)
	UBaseStatSpecification* BaseStats;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> Stats;

	UPROPERTY(EditAnywhere)
	FString DisplayName = "";

	UPROPERTY(EditAnywhere)
	USceneComponent* UpperAttachmentPoint;

	UPROPERTY(EditAnywhere)
	USceneComponent* CenterAttachmentPoint;

	UPROPERTY(EditAnywhere)
	USceneComponent* LowerAttachmentPoint;

	//TArray<>

private:
	int ActiveParticleEffectHandle = 0;
};


