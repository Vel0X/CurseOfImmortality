// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Engine/GameInstance.h"
#include "GameController.generated.h"

class AAttackManager;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UGameController : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void OnStart() override;
public:
	void BindAbilityController(AAttackManager* _AttackManager);
	AAttackManager* GetAttackManager() const;

	TArray<AActor*> GetEnemies() const;
	void AddEnemy(AActor* Enemy);
	
private:
	UPROPERTY(EditAnywhere)
	AAttackManager* AttackManager;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> ActiveEnemies;
};
