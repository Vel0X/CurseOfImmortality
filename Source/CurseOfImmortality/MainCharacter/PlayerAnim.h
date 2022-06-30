// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

protected:
	
	//Base Animation Durations
	UPROPERTY(EditAnywhere, Category="Time")
	float BaseMeleeDuration1 = 0.372f;
	UPROPERTY(EditAnywhere, Category="Time")
	float BaseMeleeDuration2 = 0.267f;
	UPROPERTY(EditAnywhere, Category="Time")
	float BaseMeleeDuration3 = 0.694f;
	UPROPERTY(EditAnywhere, Category="Time")
	float BaseMeleeDuration = 1.333f;
	UPROPERTY(EditAnywhere, Category="Time")
	float BaseRangedDuration1 = 0.5166665f;
	UPROPERTY(EditAnywhere, Category="Time")
	float BaseSpecialDuration1 = 0.4492752f;
	UPROPERTY(EditAnywhere, Category="Time")
	float BaseDashDuration1 = 0.15f;
	
public:

	void SyncAnimAttackSpeed(float PlayerAttackSpeed);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AnimationFinished = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FireRanged = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FireSpecial = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed = 1.0f;

	//Dynamic Animation Durations
	UPROPERTY(EditAnywhere, Category="Time")
	float MeleeDuration1 = 0.372f;
	UPROPERTY(EditAnywhere, Category="Time")
	float MeleeDuration2 = 0.267f;
	UPROPERTY(EditAnywhere, Category="Time")
	float MeleeDuration3 = 0.694f;
	UPROPERTY(EditAnywhere, Category="Time")
	float MeleeDuration = 1.333f;
	UPROPERTY(EditAnywhere, Category="Time")
	float RangedDuration1 = 0.5166665f;
	UPROPERTY(EditAnywhere, Category="Time")
	float SpecialDuration1 = 0.5333335f;
	UPROPERTY(EditAnywhere, Category="Time")
	float DashDuration1 = 0.25f;

	//States
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Idle = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Running = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Melee = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Ranged = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Special = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Dash = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Stunned = false;
};
