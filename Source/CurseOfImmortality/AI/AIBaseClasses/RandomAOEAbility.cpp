// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomAOEAbility.h"

#include "AIDamageObject.h"
#include "Components/SphereComponent.h"
#include "CurseOfImmortality/AI/StormCaller/StormCallerPawn.h"
#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/DolomarsWrath.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/AbilitySpecification.h"
#include "Kismet/GameplayStatics.h"

void URandomAOEAbility::StartAbility(UAbilitySpecification* AbilitySpecification)
{
	FVector PlayerLocation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
	PlayerLocation.Z = 0;

	for (int i = 0; i < Amount; ++i)
	{
		const FVector2d RandomPoint = FMath::RandPointInCircle(RangeAroundPlayer);
		FVector RandomPoint3D(RandomPoint, 0);

		FVector DamageFieldLocation = PlayerLocation + RandomPoint3D;

		if (AbilitySpecification == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("No Abiltiy Specification in Random AOE Ability!"));
			return;
		}

		ADolomarsWrath* AbilityInstance = Cast<ADolomarsWrath>(
			GetWorld()->SpawnActor(AbilitySpecification->Class, &DamageFieldLocation, &FRotator::ZeroRotator));
		AbilityInstance->Collider->SetSphereRadius(DamageField);

		if (AbilityInstance == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Abiltiy could not be spawned in Random AOE Ability!"));
			return;
		}
	}
}
