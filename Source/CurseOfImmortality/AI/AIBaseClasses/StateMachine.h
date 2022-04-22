// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine.generated.h"

class UState;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CURSEOFIMMORTALITY_API UStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStateMachine();
	
	virtual void Transition(UState* NewState, UStateMachine* Controller);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY()
	UState* CurrentState;
};
