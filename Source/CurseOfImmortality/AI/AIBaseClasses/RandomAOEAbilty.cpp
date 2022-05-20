// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomAOEAbilty.h"

#include "AIDamageObject.h"
#include "Components/SphereComponent.h"
#include "CurseOfImmortality/AI/StormCaller/StormCallerPawn.h"
#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/DolomarsWrath.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/AbilitySpecification.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
URandomAOEAbilty::URandomAOEAbilty()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URandomAOEAbilty::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void URandomAOEAbilty::StartAbility(UAbilitySpecification* AbilitySpecification)
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


// Called every frame
void URandomAOEAbilty::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
