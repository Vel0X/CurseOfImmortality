// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "StormCallerStateMachine.generated.h"

class AStormCallerPawn;
class ABaseCharacter;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UStormCallerStateMachine : public UStateMachine
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void FocusOnPlayer(float DeltaTime);

	//States
	UPROPERTY()
	UState* Idle;
	UPROPERTY(BlueprintReadOnly)
	UState* Attack;

	//Getter
	AStormCallerPawn* GetSelfRef() const;
	ABaseCharacter* GetPlayer() const;

protected:
	virtual void BeginPlay() override;

private:
	//References
	UPROPERTY()
	AStormCallerPawn* SelfRef;
	UPROPERTY()
	ABaseCharacter* Player;
};
