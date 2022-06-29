// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomAOEAbility.h"

#include "Components/SphereComponent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/DolomarsWrath.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/AbilitySpecification.h"
#include "Kismet/GameplayStatics.h"
#include "Pathfinding/PathfindingGrid.h"

void URandomAOEAbility::StartAbility(UAbilitySpecification* AbilitySpecification, ABaseCharacter* Caster)
{
	const FVector PlayerLocation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();

	for (int i = 0; i < Amount; ++i)
	{
		FVector DamageFieldLocation = GetAttackLocation(PlayerLocation);

		if (AbilitySpecification == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("No Abiltiy Specification in Random AOE Ability!"));
			return;
		}

		ADolomarsWrath* AbilityInstance = Cast<ADolomarsWrath>(
			GetWorld()->SpawnActor(AbilitySpecification->Class, &DamageFieldLocation, &FRotator::ZeroRotator));

		AbilityInstance->InitializeAbility(Caster, 1, AbilitySpecification);

		if (AbilityInstance == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Abiltiy could not be spawned in Random AOE Ability!"));
			return;
		}
	}
}

FVector URandomAOEAbility::GetAttackLocation(FVector PlayerLocation) const
{
	int Index = 0;

	while (Index <= 10000)
	{
		const FVector2d RandomPoint = FMath::RandPointInCircle(RangeAroundPlayer);
		FVector RandomPoint3D(RandomPoint, PlayerLocation.Z);
		RandomPoint3D += PlayerLocation;

		APathfindingGrid* Grid = FPersistentWorldManager::PathfindingGrid;

		if (Grid->CoordinatesWalkable(RandomPoint3D))
		{
			return RandomPoint3D;
		}

		Index++;
	}

	return FVector::Zero();
}
