// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneReplicator.h"

#include "CurseOfImmortality/BaseClasses/GameController.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/SpecialAbility.h"
#include "CurseOfImmortality/UpgradeSystem/IndirectAbilities/ArcaneReplicatorTurret.h"

void UArcaneReplicator::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
}

void UArcaneReplicator::OnAbilityStart(int AbilityHandle)
{
	Super::OnAbilityStart(AbilityHandle);
	ASpecialAbility* Owner = static_cast<ASpecialAbility*>(GetOwner());
	if(Owner != nullptr)
	{
		//FVector Forward = Owner->GetActorForwardVector();
		const auto TurretClass = static_cast<UGameController*>(Owner->GetGameInstance())->GetAttackManager()->ArcaneReplicatorTurretBP;
		AActor* Turret = GetWorld()->SpawnActor(TurretClass);
		if(Turret != nullptr)
		{
			const auto TurretCasted = static_cast<ABaseAbility*>(Turret);
			if(TurretCasted != nullptr)
			{
				TurretCasted->SetActorLocation(Owner->GetActorLocation());
				Owner->Parent = Turret;
				TurretCasted->AbilityLifetime = Owner->AbilityLifetime;
				TurretCasted->ResetLifetime();
			}
		}
	}
}
