// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "BuffSpecification.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UBuffSpecification final : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EBuff> BuffType;

	UPROPERTY(EditAnywhere)
	FString DisplayName = "";

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseBuff> Class;
	
	UPROPERTY(EditAnywhere)
	float BuffDuration;
	
	//might need an array for this later
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ParticleSystem;
	
	//when this buff is already on an object multiple iterations can be stacked atop of each other
	UPROPERTY(EditAnywhere)
	bool Stackable;

	//ignore BuffDuration and instead remove the Buff at an arbitrary point in time
	UPROPERTY(EditAnywhere)
	bool CustomBuffEnd = false;

	UPROPERTY(EditAnywhere)
	bool InheritRotation = false;
	
	UPROPERTY(EditAnywhere)
	bool StatModifier = false;

	UPROPERTY(EditAnywhere)
	bool RefreshOnNew = false;
	
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> StatModifications;
};
