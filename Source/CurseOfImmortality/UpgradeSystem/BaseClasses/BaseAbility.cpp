// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"
#include "BaseUpgrade.h"
#include "NiagaraCommon.h"
#include "RangedAbility.h"
#include "Components/ShapeComponent.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageComponent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/Utility/DetachedParticleActor.h"
#include "Niagara/Public/NiagaraComponent.h"

// Sets default values
ABaseAbility::ABaseAbility()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageComponent = CreateDefaultSubobject<UDamageComponent>("DamageComponent");
}


// Called when the game starts or when spawned
void ABaseAbility::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAbility::CheckCollisions()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	//UE_LOG(LogTemp, Warning, TEXT("Number of overlapping Actors: %i"), OverlappingActors.Num());

	bool EnemyHit = false;
	for (auto OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
		{
			ABaseCharacter* OverlappingCharacter = static_cast<ABaseCharacter*>(OverlappingActor);

			if (InitialCollisions.Contains(OverlappingCharacter))
				continue;

			OnHitNotify(OverlappingCharacter);
			
			if (!NoFaction)
			{
				if (Caster == nullptr)
				{
					//UE_LOG(LogTemp, Warning, TEXT("CASTER IS NULL"));
					continue;
				}

				if (OverlappingCharacter->Faction == Caster->Faction)
					continue;
			}

			EnemyHit = true;

			auto CharacterHitboxes = OverlappingCharacter->BodyHitboxes;

			for (const auto AbilityHitbox : HitBoxes)
			{
				for (const auto CharacterHitbox : CharacterHitboxes)
				{
					if (AbilityHitbox->IsOverlappingComponent(CharacterHitbox))
					{
						//auto Loc = Info.OverlapInfo.Location;
						//UE_LOG(LogTemp, Warning, TEXT("L %f, %f, %f"), Loc.X, Loc.Y, Loc.Z);
						if(DamageComponent->OnCharacterHit(AbilityHitbox, OverlappingCharacter, CharacterHitbox))
						{
							OnCharacterHit(OverlappingCharacter);

							if(EnemyHitSound != "")
								FPersistentWorldManager::SoundManager->PlaySoundLocated(GetActorLocation(), EnemyHitSound);
						}
					}
				}

				/*
				if(OtherActor->GetClass()->IsChildOf(ARangedAbility::StaticClass()))
				{
					ARangedAbility* OtherAbility = static_cast<ARangedAbility*>(OtherActor);
					UE_LOG(LogTemp, Error, TEXT("Hit other Ability"));
					for (const auto Upgrade : UpgradeStack)
					{
						Upgrade->OnAbilityHit(OtherAbility);
					}

				}
				*/
				//Handling hitting other Abilities
			}
		}
		else if(OverlappingActor->GetClass()->IsChildOf(ARangedAbility::StaticClass()))
		{
			UE_LOG(LogTemp, Error, TEXT("Hit other Ability"));
		}
		else
		{
			if(DestroyOnEnemyHit)
			{
				if(WallHitSound != "")
					FPersistentWorldManager::SoundManager->PlaySoundLocated(GetActorLocation(), WallHitSound);
				
				if(DestructionVfx)
				{
					const FVector SpawnLocation = GetActorLocation();
					const auto DetachedParticleActor = GetWorld()->SpawnActor<ADetachedParticleActor>();
					DetachedParticleActor->InitializeParticleActor(SpawnLocation, DestructionVfx, nullptr, 0.8f);
				}
				DestroyAbility();
			}
		}

	}

	if (EnemyHit && DestroyOnEnemyHit)
		DestroyAbility();
}

void ABaseAbility::OnCharacterHit(ABaseCharacter* OverlappingCharacter)
{
	for (const auto Upgrade : UpgradeStack)
	{
		Upgrade->OnEnemyHit(OverlappingCharacter);
	}
}

void ABaseAbility::OnAbilityCreation()
{
}

// Called every frame
void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RemainingAbilityLifetime -= DeltaTime;

	if (RemainingAbilityLifetime <= 0.0f)
	{
		DestroyAbility();
	}
	if (!CanInteract)
	{
		if (IgnoreInitialCollisions)
		{
			CanInteract = true;
			return;
		}

		//Initial Collision Check
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors);

		//UE_LOG(LogTemp, Warning, TEXT("Number of overlapping Actors: %i"), OverlappingActors.Num());

		for (auto OverlappingActor : OverlappingActors)
		{
			if (OverlappingActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
			{
				ABaseCharacter* OverlappingCharacter = Cast<ABaseCharacter>(OverlappingActor);

				//OnHitNotify(OverlappingCharacter);
				
				if (!Caster)
				{
					//UE_LOG(LogTemp, Warning, TEXT("CASTER IS NULL"));
					continue;
				}

				if (OverlappingCharacter->Faction == Caster->Faction)
					continue;

				auto CharacterHitboxes = OverlappingCharacter->BodyHitboxes;

				for (const auto AbilityHitbox : HitBoxes)
				{
					for (const auto CharacterHitbox : CharacterHitboxes)
					{
						if (AbilityHitbox->IsOverlappingComponent(CharacterHitbox))
						{
							InitialCollisions.Add(OverlappingCharacter);
						}
					}
				}
			}
		}

		//UE_LOG(LogTemp, Warning, TEXT("Hit %i Actors in Start"), InitialCollisions.Num());
		CanInteract = true;
	}

	CheckCollisions();
}

void ABaseAbility::OnHitNotify(ABaseCharacter* HitCharacter)
{
}


void ABaseAbility::AfterInitialization()
{
	for (const auto Upgrade : UpgradeStack)
	{
		if (Upgrade == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL in list"));
		}
		else
		{
			Upgrade->OnAbilityStart();
		}
	}

	//set params of ability
	const FVector NewScale = FVector(RelativeSize, RelativeSize, RelativeSize);
	SetActorScale3D(NewScale);

	/*
	TArray<AActor*> Overlapping;
	GetOverlappingActors(Overlapping);
	UE_LOG(LogTemp, Warning, TEXT("Overlapping %i"), Overlapping.Num());
	
	for (const auto Actor : Overlapping)
	{
		OnEnemyHit(this, Actor);
	}
	*/
}

void ABaseAbility::DestroyAbility()
{
	//OnAbilityEnd.Broadcast(AbilityHandle);
	for (const auto Upgrade : UpgradeStack)
	{
		if (Upgrade == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL in list"));
		}
		else
		{
			Upgrade->OnAbilityEnd();
		}
	}
	//const UNiagaraComponent* vfx = FindComponentByClass<UNiagaraComponent>();
	/*
		if(vfx == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found no vfx"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("found vfx"));
	
			//vfx->GetAsset()->Destro
	
		}
		*/
	if(!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("wordl null????"));
		return;
	}

	Destroy();

}

void ABaseAbility::InitializeAbility(ABaseCharacter* _Caster, int Level, const UAbilitySpecification* Specification)
{
	Caster = _Caster;
	AbilityLevel = Level;

	RemainingAbilityLifetime = AbilityLifetime;
	//OnActorBeginOverlap.AddDynamic( this, &ABaseAbility::OnEnemyHit);
	//UE_LOG(LogTemp, Warning, TEXT("AbilityInstance was spawned (Base)"));
	//OnActorBeginOverlap.AddDynamic(this, &ABaseAbility::AtOverlap);

	//get all the colliders and store them in an array
	TArray<UActorComponent*> HBs;
	GetComponents(UPrimitiveComponent::StaticClass(), HBs);
	for (const auto Component : HBs)
	{
		//add all primitive Components that generate Overlap Events
		auto PrimitiveComponent = static_cast<UPrimitiveComponent*>(Component);
		if (PrimitiveComponent->GetCollisionProfileName() == "Ability")
		{
			HitBoxes.Add(PrimitiveComponent);
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Ability contains %i Colliders"), HitBoxes.Num());
	DamageComponent->ConvertInterface();

	if(Specification)
	{
		DestructionVfx = Specification->DestructionVfx;
		CastSound = Specification->CastSound;
		EnemyHitSound = Specification->EnemyHitSound;
		WallHitSound = Specification->WallHitSound;

		if(CastSound != "")
			FPersistentWorldManager::SoundManager->PlaySoundLocated(GetActorLocation(), CastSound);
	}
}

void ABaseAbility::AddUpgrade(const TSubclassOf<UBaseUpgrade>& Class, int UpgradeLevel)
{
	UBaseUpgrade* Upgrade = Cast<UBaseUpgrade>(AddComponentByClass(Class, false, FTransform::Identity, false));
	if (Upgrade == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL after cast"));
	}
	else
	{
		Upgrade->InitializeUpgrade(this, UpgradeLevel);
		UpgradeStack.Add(Upgrade);
	}
}

void ABaseAbility::ResetLifetime()
{
	RemainingAbilityLifetime = AbilityLifetime;
}
