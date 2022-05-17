// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"
#include "BaseUpgrade.h"
#include "NiagaraCommon.h"
#include "Components/ShapeComponent.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageComponent.h"
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
	RemainingAbilityLifetime = AbilityLifetime;
	OnActorBeginOverlap.AddDynamic( this, &ABaseAbility::OnEnemyHit);
	//UE_LOG(LogTemp, Warning, TEXT("AbilityInstance was spawned (Base)"));
	//OnActorBeginOverlap.AddDynamic(this, &ABaseAbility::AtOverlap);
	
	//get all the colliders and store them in an array
	TArray<UActorComponent*> HBs;
	GetComponents(UPrimitiveComponent::StaticClass(), HBs);
	for (const auto Component : HBs)
	{

		//add all primitive Components that generate Overlap Events
		auto PrimitiveComponent = static_cast<UPrimitiveComponent*>(Component);
		if(PrimitiveComponent->GetGenerateOverlapEvents())
		{
			HitBoxes.Add(PrimitiveComponent);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Ability contains %i Colliders"), HitBoxes.Num());

	DamageComponent->ConvertInterface();


}

void ABaseAbility::CheckCollisions()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	//UE_LOG(LogTemp, Warning, TEXT("Number of overlapping Actors: %i"), OverlappingActors.Num());

	for (auto OverlappingActor : OverlappingActors)
	{
		if(OverlappingActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
		{
			ABaseCharacter* OverlappingCharacter = static_cast<ABaseCharacter*>(OverlappingActor);
			auto CharacterHitboxes = OverlappingCharacter->HitBoxes;

			for (const auto AbilityHitbox : HitBoxes)
			{
				for (const auto CharacterHitbox : CharacterHitboxes)
				{
					if(AbilityHitbox->IsOverlappingComponent(CharacterHitbox))
					{
						DamageComponent->OnCharacterHit(AbilityHitbox, OverlappingCharacter);
					}
				}
			}
		}
	}
}

void ABaseAbility::OnEnemyHit(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
	{
		if(!CanInteract)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Enemy during Initialization"));
			return;
		}
		
		ABaseCharacter* OtherChar = static_cast<ABaseCharacter*>(OtherActor);
		if(Caster == OtherChar)
		{
			return;
		}
		OtherChar->TakeDmg(10,  Caster, this, false);


		
		UE_LOG(LogTemp, Warning, TEXT("Enemy was hit"));
		for (const auto Upgrade : UpgradeStack)
		{
			if(Upgrade == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL in list"));
			}
			else
			{
				Upgrade->OnEnemyHit(OtherChar);
			}
		}
		

		if(DestroyOnEnemyHit)
		{
			UE_LOG(LogTemp, Error, TEXT("Ability was destroyed on Enemyhit"));
			DestroyAbility();
		}

		return;
	}

	if(OtherActor->GetClass()->IsChildOf(ARangedAbility::StaticClass()))
	{
		ARangedAbility* OtherAbility = static_cast<ARangedAbility*>(OtherActor);
		UE_LOG(LogTemp, Error, TEXT("Hit other Ability"));
		for (const auto Upgrade : UpgradeStack)
		{
			Upgrade->OnAbilityHit(OtherAbility);
		}

	}
	//Handling hitting other Abilities
}

void ABaseAbility::OnAbilityCreation()
{
}

// Called every frame
void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RemainingAbilityLifetime -= DeltaTime;
	if(RemainingAbilityLifetime <= 0.0f)
	{
		DestroyAbility();
	}
	CanInteract = true;

	CheckCollisions();
}

void ABaseAbility::AfterInitialization()
{
	for (const auto Upgrade : UpgradeStack)
	{
		if(Upgrade == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL in list"));
		}
		else
		{
			Upgrade->OnAbilityStart(AbilityHandle);
		}
	}

	//set params of ability
	const FVector NewScale = FVector(RelativeSize, RelativeSize, RelativeSize);
	SetActorScale3D(NewScale);

	TArray<AActor*> Overlapping;
	GetOverlappingActors(Overlapping);
	UE_LOG(LogTemp, Warning, TEXT("Overlapping %i"), Overlapping.Num());
	
	for (const auto Actor : Overlapping)
	{
		OnEnemyHit(this, Actor);
	}
}

void ABaseAbility::DestroyAbility()
{
	
	//OnAbilityEnd.Broadcast(AbilityHandle);
	for (const auto Upgrade : UpgradeStack)
	{
		if(Upgrade == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL in list"));
		}
		else
		{
			Upgrade->OnAbilityEnd(AbilityHandle);
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
	Destroy();
}

void ABaseAbility::InitializeAbility(int _AbilityHandle, ABaseCharacter* _Caster, int Level)
{
	Caster = _Caster;
}

void ABaseAbility::AddUpgrade(const TSubclassOf<UBaseUpgrade>& Class, int UpgradeLevel)
{
	/*
	auto Upgrade = AddComponentByClass(Class, false, GetTransform(), false);

	if(Upgrade == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Upgrade was NULL after cast"));
	}
	*/
	
	UBaseUpgrade* Upgrade = static_cast<UBaseUpgrade*>(AddComponentByClass(Class, false, FTransform::Identity, false));
	if(Upgrade == nullptr)
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

