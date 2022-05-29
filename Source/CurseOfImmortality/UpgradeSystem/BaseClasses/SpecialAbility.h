// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "SpecialAbility.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API ASpecialAbility : public ABaseAbility
{
	GENERATED_BODY()
public:
	virtual void InitializeAbility(int _AbilityHandle, ABaseCharacter* _Caster, int Level) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Parent;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAttachmentPoint> AttachmentPoint;
protected:
	virtual void Tick(float DeltaSeconds) override;
};
