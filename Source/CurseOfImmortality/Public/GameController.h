// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/GameDummy/MainChar.h"
#include "Engine/GameInstance.h"
#include "GameController.generated.h"

class UAttackManager;
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
	void BindAbilityController(UAttackManager* _AttackManager);
	UAttackManager* GetAttackManager() const;

	TArray<AActor*> GetEnemies() const;
	void AddEnemy(AActor* Enemy);

	AMainChar* GetMainChar() const;
	void SetMainChar(AMainChar* _MainChar);
private:
	UPROPERTY(EditAnywhere)
	UAttackManager* AttackManager;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> ActiveEnemies;

	UPROPERTY(EditAnywhere)
	AMainChar* MainChar;
};
