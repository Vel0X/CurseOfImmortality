// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "BaseBuff.generated.h"

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
	
	UFUNCTION()
	virtual void OnTakeDamage(ABaseAbility* Ability);

	virtual void AddBuffStack();

	virtual void OnBuffBegin();

	virtual void OnBuffTick(float DeltaTime);
	
	virtual void OnBuffEnd();

	virtual void InitializeBuff(int Level, AChar* _Owner);

	//virtual UNiagaraSystem* GetVFX() const;

	virtual UNiagaraComponent* SetupVfx(EAttachmentPoint AttachmentPoint);

	virtual void DestroyVfx();
	
	UPROPERTY(EditAnywhere)
	AChar* Owner;

	FString DisplayName = "";

	TEnumAsByte<EBuff> BuffType;
	
	UPROPERTY(EditAnywhere)
	float BuffDuration;

	float RemainingDuration;
	
	//when this buff is already on an object multiple iterations can be stacked atop of each other
	UPROPERTY(EditAnywhere)
	bool Stackable;
	
	UPROPERTY(EditAnywhere)
	int CurrentStacks;

	//ignore BuffDuration and instead remove the Buff at an arbitrary point in time
	UPROPERTY(EditAnywhere)
	bool CustomBuffEnd = false;

	UPROPERTY(EditAnywhere)
	bool StatModifier = false;

	UPROPERTY(EditAnywhere)
	bool RefreshOnNew = false;

	int DefaultHandle = -1;
	
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> StatModifications; 
};
