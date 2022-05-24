// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "TrapComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURSEOFIMMORTALITY_API UTrapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrapComponent();
	UPROPERTY(BlueprintReadOnly)
	bool TrapIsActive = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Prio = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETrapTypes> TrapType;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(Exec)
	void CheckActivation(TEnumAsByte<ETrapTypes> OthertrapType, int priority);
	UFUNCTION(Exec)
	void CheckDeactivation(TEnumAsByte<ETrapTypes> OthertrapType, int priority);

		
};
