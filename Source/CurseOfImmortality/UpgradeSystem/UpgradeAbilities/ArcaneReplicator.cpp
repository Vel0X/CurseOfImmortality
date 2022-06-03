// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneReplicator.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/SpecialAbility.h"
#include "CurseOfImmortality/UpgradeSystem/IndirectAbilities/ArcaneReplicatorTurret.h"

void UArcaneReplicator::InitializeUpgrade(ABaseAbility* _AbilityInstance, int UpgradeLevel)
{
	Super::InitializeUpgrade(_AbilityInstance, UpgradeLevel);
}

void UArcaneReplicator::OnAbilityStart()
{
	Super::OnAbilityStart();
	ASpecialAbility* Owner = Cast<ASpecialAbility>(AbilityInstance);
	if(Owner != nullptr)
	{
		
		//FVector Forward = Owner->GetActorForwardVector();
		const auto TurretClass = FPersistentWorldManager::AttackManager->ArcaneReplicatorTurretBP;
		AActor* InstantiatedActor = GetWorld()->SpawnActor(TurretClass);
		AArcaneReplicatorCrab* Turret = Cast<AArcaneReplicatorCrab>(InstantiatedActor);
		if(Turret != nullptr)
		{
			Turret->SetActorLocation(Owner->GetActorLocation());
			Owner->Parent = Turret->GetAttachmentLocation(Owner->AttachmentPoint);
			Turret->Initialize(Owner->Caster->GetActorForwardVector(), Owner->AbilityLifetime);
		}
	}
}
