// Fill out your copyright notice in the Description page of Project Settings.


#include "SealOfCongruence.h"
#include "GameController.h"
#include "AttackManager.h"
#include "Kismet/KismetMathLibrary.h"

static float AngleBetweenProjectiles = 30.0f;

void USealOfCongruence::OnAbilityStart(int AbilityHandle)
{
	Super::OnAbilityStart(AbilityHandle);
	if(ChargesLeft == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Charges left (Seal of Congruence) %d"), ChargesLeft);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Instantiating new projectiles (Seal of Congruence) %d"), ChargesLeft);
	ChargesLeft--;
	
	const AAttackManager* AttackManager = static_cast<UGameController*>(GetOwner()->GetGameInstance())->GetAttackManager();

	ABaseAbility* Owner = static_cast<ABaseAbility*>(GetOwner());
	if(Owner != nullptr)
	{
		FVector Direction = Owner->GetActorForwardVector();
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
					AttackManager->SpawnFromTemplate(Owner, Rotation);
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

void USealOfCongruence::OnAbilityEnd(int AbilityHandle)
{
	Super::OnAbilityEnd(AbilityHandle);
	UE_LOG(LogTemp, Warning, TEXT("On Abilityend was called in Seal of Congruence Upgrade"));
 
}
