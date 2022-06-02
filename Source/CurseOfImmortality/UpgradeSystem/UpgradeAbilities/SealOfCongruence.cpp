// Fill out your copyright notice in the Description page of Project Settings.


#include "SealOfCongruence.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "Kismet/KismetMathLibrary.h"

static float AngleBetweenProjectiles = 30.0f;

void USealOfCongruence::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
	switch(UpgradeLevel)
	{
	case 1:
		Projectiles = 3;
		break;
	case 2:
		Projectiles = 5;
		break;
	case 3:
		Projectiles = 7;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Invalid Upgradelevel for Seal of Congruence"));
		break;
	}
}

void USealOfCongruence::OnAbilityStart()
{
	Super::OnAbilityStart();
	if(ChargesLeft == 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("No Charges left (Seal of Congruence) %d"), ChargesLeft);
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Instantiating new projectiles (Seal of Congruence) %d"), ChargesLeft);
	ChargesLeft--;
	
	const UAttackManager* AttackManager = FPersistentWorldManager::AttackManager;

	if(AbilityInstance != nullptr)
	{
		FVector Direction = AbilityInstance->GetActorForwardVector();//FVector(1,0,0); //
		const float AngleChange = (Projectiles-1) * AngleBetweenProjectiles;
		const FRotator StartRotator = FRotator(0.0f,-(AngleChange / 2.0f), 0.0f);
		const FRotator OngoingRotator = FRotator(0.0f, AngleBetweenProjectiles, 0.0f);
		Direction = StartRotator.RotateVector(Direction);

		if(Projectiles % 2 != 0)
		{
			for (int i = 0; i < Projectiles; ++i)
			{
				if((Projectiles-1)/2 != i)
				{
					const FRotator Rotation = UKismetMathLibrary::Conv_VectorToRotator(Direction);
					AttackManager->SpawnFromTemplate(AbilityInstance, AbilityInstance->GetActorLocation(), Rotation);
				}

				Direction = OngoingRotator.RotateVector(Direction);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner couldn't be cast (Seal of Congruence) %d"), ChargesLeft);
	}
}


