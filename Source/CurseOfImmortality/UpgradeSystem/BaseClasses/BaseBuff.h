// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "BaseBuff.generated.h"

class UNiagaraSystem;
class UBuffSpecification;
class ABaseCharacter;
class UNiagaraComponent;
class ABaseAbility;
class AChar;

UCLASS()
class CURSEOFIMMORTALITY_API UBaseBuff : public UObject
{
	GENERATED_BODY()

public:	
	UBaseBuff();

	void SetupBuff(UBuffSpecification* Specification);
	
	UFUNCTION()
	virtual void OnTakeDamage(ABaseAbility* Ability);
	virtual void OnDealDamage(float Amount, ABaseCharacter* Recipient);
	virtual bool AddBuffStack();
	virtual void OnBuffBegin();
	virtual void OnBuffTick(float DeltaTime);
	virtual void OnBuffEnd();
	virtual void InitializeBuff(int Level, ABaseCharacter* _Owner, ABaseCharacter* _Inflicter);
	virtual UNiagaraComponent* SetupVfx(EAttachmentPoint AttachmentPoint);
	virtual void DestroyVfx();

	//who inflicted this buff
	UPROPERTY(EditAnywhere)
	ABaseCharacter* Inflicter;

	//who this buff is on
	UPROPERTY(EditAnywhere)
	ABaseCharacter* Owner;

	FString DisplayName = "";

	TEnumAsByte<EBuff> BuffType;
	
	float BuffDuration;
	float RemainingDuration;

	//might need an array for this later
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystemComponent;

	//
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ParticleSystem;
	
	//when this buff is already on an object multiple iterations can be stacked atop of each other
	int CurrentStacks = 1;

	int BuffLevel = 1;
	
	bool Stackable;
	int MaxStacks = 1;
	bool CustomBuffEnd = false;
	bool InheritRotation = false;
	bool StatModifier = false;
	bool RefreshOnNew = false;

	int DefaultHandle = -1;
	
	TMap<TEnumAsByte<EStats>, float> StatModifications; 
	TMap<TEnumAsByte<EStats>, float> StatModificationsPerStack;
};
