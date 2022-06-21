// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/Traps/BaseTrap.h"

#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageComponent.h"
#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/Fireball.h"
#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/TrapProjectile.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/AbilitySpecification.h"

// Sets default values
ABaseTrap::ABaseTrap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageComponent = CreateDefaultSubobject<UDamageComponent>("TrapDamage");
}

// Called when the game starts or when spawned
void ABaseTrap::BeginPlay()
{
	Super::BeginPlay();

	InitializeAbility();
}

// Called every frame
void ABaseTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckCollisions();
}

void ABaseTrap::InitializeAbility()
{
	//get all the colliders and store them in an array
	TArray<UActorComponent*> HBs;
	GetComponents(UPrimitiveComponent::StaticClass(), HBs);
	for (const auto Component : HBs)
	{
		//add all primitive Components that generate Overlap Events
		auto PrimitiveComponent = Cast<UPrimitiveComponent>(Component);
		if (PrimitiveComponent->GetCollisionProfileName() == "Ability")
		{
			HitBoxes.Add(PrimitiveComponent);
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Ability contains %i Colliders"), HitBoxes.Num());
	DamageComponent->ConvertInterface();
}

void ABaseTrap::CheckCollisions()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (auto OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
		{
			ABaseCharacter* OverlappingCharacter = Cast<ABaseCharacter>(OverlappingActor);

			auto CharacterHitboxes = OverlappingCharacter->BodyHitboxes;

			for (const auto AbilityHitbox : HitBoxes)
			{
				for (const auto CharacterHitbox : CharacterHitboxes)
				{
					if (AbilityHitbox->IsOverlappingComponent(CharacterHitbox))
					{
						DamageComponent->OnCharacterHit(AbilityHitbox, OverlappingCharacter);
					}
				}
			}
		}
	}
}

void ABaseTrap::FireProjectile(FVector SpawnLocation, FRotator SpawnRotation)
{
	// UE_LOG(LogTemp,Warning,TEXT("Fire"))
	ATrapProjectile* AbilityInstance = Cast<ATrapProjectile>(GetWorld()->SpawnActor(
		ProjectileSpecification->Class,
		&SpawnLocation, &SpawnRotation));
	if (!AbilityInstance) { return; }
	AbilityInstance->NoFaction = true;
	AbilityInstance->InitializeAbility(nullptr, 1, nullptr);
}
