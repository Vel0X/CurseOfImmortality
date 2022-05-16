// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "BaseBuff.generated.h"

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
	// Sets default values for this component's properties
	UBaseBuff();

	void SetupBuff(UBuffSpecification* Specification);
	
	UFUNCTION()
	virtual void OnTakeDamage(ABaseAbility* Ability);
	virtual void AddBuffStack();
	virtual void OnBuffBegin();
	virtual void OnBuffTick(float DeltaTime);
	virtual void OnBuffEnd();
	virtual void InitializeBuff(int Level, ABaseCharacter* _Owner);
	virtual UNiagaraComponent* SetupVfx(EAttachmentPoint AttachmentPoint);
	virtual void DestroyVfx();
	
	UPROPERTY(EditAnywhere)
	ABaseCharacter* Owner;

	FString DisplayName = "";

	TEnumAsByte<EBuff> BuffType;
	
	float BuffDuration;
	float RemainingDuration;

	//might need an array for this later
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystem;
	
	//when this buff is already on an object multiple iterations can be stacked atop of each other
	int CurrentStacks;

	bool Stackable;
	bool CustomBuffEnd = false;
	bool InheritRotation = false;
	bool StatModifier = false;
	bool RefreshOnNew = false;

	int DefaultHandle = -1;
	
	TMap<TEnumAsByte<EStats>, float> StatModifications;
};
