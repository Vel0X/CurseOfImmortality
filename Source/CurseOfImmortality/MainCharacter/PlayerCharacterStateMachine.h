// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "PlayerCharacterStateMachine.generated.h"

enum class InputAction;
class APlayerCharacter;

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UPlayerCharacterStateMachine : public UStateMachine
{
	GENERATED_BODY()
	
public:
	UPlayerCharacterStateMachine();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
	void Initialize();
	
	//States
	UPROPERTY()
	UState* Idle;
	UPROPERTY()
	UState* Running;
	UPROPERTY()
	UState* MeleeAttack;
	UPROPERTY()
	UState* RangedAttack;
	UPROPERTY()
	UState* SpecialAttack;
	UPROPERTY()
	UState* Dash;

	//Getter
	APlayerCharacter* GetSelfRef() const;
	
	InputAction* NewAction;
	
protected:
	virtual void BeginPlay() override;

private:
	//References
	UPROPERTY()
	APlayerCharacter* SelfRef;

};
