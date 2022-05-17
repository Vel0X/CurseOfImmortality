// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurseOfImmortality/Enums/Enums.h"
#include "TrapManagerCopmonent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURSEOFIMMORTALITY_API UTrapManagerCopmonent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrapManagerCopmonent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateAllTrapsOfType(ETrapTypes Type);
	void DeactivateAllTrapsOfType(ETrapTypes Type);
	void UpgradeTrapsOfType(ETrapTypes Type);

	
		
};
