// Fill out your copyright notice in the Description page of Project Settings.


#include "ShatteredImpact.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "Kismet/KismetMathLibrary.h"

void UShatteredImpact::OnEnemyHit(ABaseCharacter* Enemy)
{
	Super::OnEnemyHit(Enemy);

	FVector SpawnLocation = Enemy->GetAttachmentLocation(CenterPoint)->GetComponentLocation();

	if(!AbilityInstance->CanInteract)
	{
		return;
	}
	
	const UAttackManager* AttackManager = FPersistentWorldManager::AttackManager;
	
	if(SplitsRemaining > 0)
	{
		SplitsRemaining--;
		
		FVector Direction = AbilityInstance->GetActorForwardVector();

		const float AnglePerProjectile = 360.0f / static_cast<float>(AmountOfFragments);
		
		const FRotator StartRotator = FRotator(0.0f,-(AnglePerProjectile / 2.0f), 0.0f);
		const FRotator OngoingRotator = FRotator(0.0f, AnglePerProjectile, 0.0f);
		Direction = StartRotator.RotateVector(Direction);

		for (int i = 0; i < AmountOfFragments; ++i)
		{
			const FRotator Rotation = UKismetMathLibrary::Conv_VectorToRotator(Direction);
			AttackManager->SpawnFromTemplate(AbilityInstance, SpawnLocation, Rotation);

			Direction = OngoingRotator.RotateVector(Direction);
		}
	}
}

void UShatteredImpact::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
	switch(UpgradeLevel)
	{
	case 1:
		AmountOfFragments = 2;
		break;
	case 2:
		AmountOfFragments = 3;
		break;
	case 3:
		AmountOfFragments = 4;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Invalid Upgradelevel for Shattered Impact"));
		break;
	}
}
