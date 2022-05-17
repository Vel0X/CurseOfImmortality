// Fill out your copyright notice in the Description page of Project Settings.


#include "ShatteredImpact.h"
#include "CurseOfImmortality/BaseClasses/GameController.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "Kismet/KismetMathLibrary.h"

void UShatteredImpact::OnEnemyHit(ABaseCharacter* Enemy)
{
	Super::OnEnemyHit(Enemy);
	ABaseAbility* Owner = static_cast<ABaseAbility*>(GetOwner());

	if(!Owner->CanInteract)
	{
		return;
	}
	
	const UAttackManager* AttackManager = static_cast<UGameController*>(GetOwner()->GetGameInstance())->GetAttackManager();

	UE_LOG(LogTemp, Warning, TEXT("OnEnemyHitTriggered"));
	
	if(SplitsRemaining > 0)
	{
		SplitsRemaining--;
		
		FVector Direction = Owner->GetActorForwardVector();

		const float AnglePerProjectile = 360.0f / static_cast<float>(AmountOfFragments);
		
		const FRotator StartRotator = FRotator(0.0f,-(AnglePerProjectile / 2.0f), 0.0f);
		const FRotator OngoingRotator = FRotator(0.0f, AnglePerProjectile, 0.0f);
		Direction = StartRotator.RotateVector(Direction);

		for (int i = 0; i < AmountOfFragments; ++i)
		{
			const FRotator Rotation = UKismetMathLibrary::Conv_VectorToRotator(Direction);
			AttackManager->SpawnFromTemplate(Owner, Rotation);

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
