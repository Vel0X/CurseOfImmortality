// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "CharacterMovement.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseBuff.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/BaseStatSpecification.h"
#include "CurseOfImmortality/UpgradeSystem/Utility/DetachedParticleActor.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Root");
	SetRootComponent(CapsuleComponent);
	//CapsuleComponent = static_cast<UCapsuleComponent*>(RootComponent);
	MovementComponent = CreateDefaultSubobject<UCharacterMovement>("CharacterMovement");
	DamageComponent = CreateDefaultSubobject<UDamageComponent>("DamageObject");
	
	UpperAttachmentPoint = CreateDefaultSubobject<USceneComponent>("UpperAttachmentPoint");
	UpperAttachmentPoint->SetupAttachment(RootComponent);
	CenterAttachmentPoint = CreateDefaultSubobject<USceneComponent>("CenterAttachmentPoint");
	CenterAttachmentPoint->SetupAttachment(RootComponent);
	LowerAttachmentPoint = CreateDefaultSubobject<USceneComponent>("LowerAttachmentPoint");
	LowerAttachmentPoint->SetupAttachment(RootComponent);
	
}

ABaseCharacter::~ABaseCharacter()
{
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	Setup();

	if(BaseStats == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no BaseStats specified for it!"), *DisplayName);
		return;
	}
	
	RecalculateStats();
	if(Stats.Contains(EStats::Health))
	{
		CurrentHealth = Stats[EStats::Health];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Stats were not properly initialized"));
	}

	//Add all Body Hitboxes
	TArray<UActorComponent*> HBs;
	GetComponents(UPrimitiveComponent::StaticClass(), HBs);
	for (const auto Component : HBs)
	{

		//add all primitive Components that generate Overlap Events and that are part of body hitbox of the character (determined by the Collision Profile)
		auto PrimitiveComponent = static_cast<UPrimitiveComponent*>(Component);
		if(PrimitiveComponent->GetCollisionProfileName() == "Character")
		{
			BodyHitboxes.Add(PrimitiveComponent);
		}
	}

	//Add all Damage Hitboxes
	for (const auto Component : HBs)
	{

		//add all primitive Components that generate Overlap Events
		auto PrimitiveComponent = static_cast<UPrimitiveComponent*>(Component);
		if(PrimitiveComponent->GetCollisionProfileName() == "Ability")
		{
			DamageHitboxes.Add(PrimitiveComponent);
		}
	}
	
	DamageComponent->ConvertInterface();
	FPersistentWorldManager::RegisterCharacter(this);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (int i = Buffs.Num() - 1; i >= 0; --i)
	{
		Buffs[i]->OnBuffTick(DeltaTime);
	}

	CheckCollisions();
}

void ABaseCharacter::CheckCollisions()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	//UE_LOG(LogTemp, Warning, TEXT("Number of overlapping Actors: %i"), OverlappingActors.Num());

	for (const auto OverlappingActor : OverlappingActors)
	{
		if(OverlappingActor->GetClass()->IsChildOf(StaticClass()))
		{
			ABaseCharacter* OverlappingCharacter = static_cast<ABaseCharacter*>(OverlappingActor);

			if(OverlappingCharacter->Faction == Faction)
				continue;
			
			auto CharacterHitboxes = OverlappingCharacter->BodyHitboxes;

			for (const auto DamageHitbox : DamageHitboxes)
			{
				for (const auto CharacterHitbox : CharacterHitboxes)
				{
					if(DamageHitbox->IsOverlappingComponent(CharacterHitbox))
					{
						DamageComponent->OnCharacterHit(DamageHitbox, OverlappingCharacter);
					}
				}
			}
		}
	}
}

void ABaseCharacter::Setup()
{
	
}

void ABaseCharacter::OnDeath()
{
	//Deactivate all Damage and BodyHitboxes
	for (auto DamageHitbox : DamageHitboxes)
		DamageHitbox->DestroyComponent();

	for (auto BodyHitBox : BodyHitboxes)
		BodyHitBox->DestroyComponent();

	DamageHitboxes.Empty();
	BodyHitboxes.Empty();
	
	Dead = true;
	FPersistentWorldManager::DeRegisterCharacter(this);
	//Destroy();
}

void ABaseCharacter::RecalculateStats()
{
	Stats.Empty();
	for (auto Stat : BaseStats->BaseStats)
	{
		Stats.Add(Stat.Key, Stat.Value);
	}
	
	for (const auto Buff : Buffs)
	{
		if(!Buff->StatModifier)
			continue;

		for (const auto StatMod : Buff->StatModifications)
		{
			Stats[StatMod.Key] += StatMod.Value;
		}
	}
}

void ABaseCharacter::AddBuff(UBaseBuff* Buff)
{
	int FoundIndex = -1;
	for (int i = 0; i < Buffs.Num(); ++i)
	{
		if(Buffs[i]->DisplayName == Buff->DisplayName)
		{
			FoundIndex = i;
			break;
		}
	}

	//if the Buff is already present...
	if(FoundIndex != -1)
	{
		//if the Buff is not stackable
		if(!Buff->Stackable)
		{
			//if the Buff should renew when it is already present
			if(Buff->RefreshOnNew)
			{
				Buffs[FoundIndex]->InitializeBuff(1, this);
				UE_LOG(LogTemp, Warning, TEXT("%s was already present and was refreshed"), *Buff->DisplayName);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s was already present and is not stackable"), *Buff->DisplayName);
				return;
			}
		}
		Buffs[FoundIndex]->AddBuffStack();
	}
	//Buff is not already present
	else
	{
		Buffs.Add(Buff);
		Buff->InitializeBuff(1,this);
		UE_LOG(LogTemp, Warning, TEXT("%s was added"), *Buff->DisplayName);
	}
	
	if(Buff->StatModifier)
		RecalculateStats();
	
}

void ABaseCharacter::RemoveBuff(UBaseBuff* Buff)
{
	if(Buffs.Contains(Buff))
	{
	UE_LOG(LogTemp, Warning, TEXT("%s was removed"), *Buff->DisplayName);
		Buffs.Remove(Buff);
		Buff->OnBuffEnd();
		if(Buff->StatModifier)
		{
			RecalculateStats();
		}
	}
}

void ABaseCharacter::TakeDmg(float Amount, ABaseCharacter* Dealer, ABaseAbility* Ability, bool Verbose)
{
	CurrentHealth -= Amount;

	if(FPersistentWorldManager::GetLogLevel(ELog::DamageComponent))
		UE_LOG(LogTemp, Warning, TEXT("After Take Damage: %s Health is at %f Max Health %f"), *DisplayName, CurrentHealth, Stats[EStats::Health]);
	
	if(CurrentHealth <= 0.0f)
	{
		OnDeath();
	}
	
	//notify all buffs of the damage taken
	
	for (int i = 0; i < Buffs.Num(); ++i)
	{
		Buffs[i]->OnTakeDamage(Ability);
	}
	
}

void ABaseCharacter::Heal(float Amount, bool Verbose)
{
	CurrentHealth += Amount;
	if(CurrentHealth > Stats[EStats::Health])
	{
		CurrentHealth = Stats[EStats::Health];
	}

	if(Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("After Heal: Char Health is at %f Max Health %f"), CurrentHealth, Stats[EStats::Health]);
	}
}

UNiagaraComponent* ABaseCharacter::SetupBuffVfx(UNiagaraSystem* Vfx, const EAttachmentPoint AttachmentPoint, int& Handle)
{
	USceneComponent* AttachmentLocation = nullptr;
	
	switch (AttachmentPoint)
	{
	case UpperPoint:
		AttachmentLocation = UpperAttachmentPoint;
		break;
	case CenterPoint:
		AttachmentLocation = CenterAttachmentPoint;
		break;
	case LowerPoint:
		AttachmentLocation = LowerAttachmentPoint;
		break;
	}
	
	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(Vfx, AttachmentLocation, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
	NiagaraComp->AttachToComponent(AttachmentLocation, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	ActiveParticleEffects.Add(ActiveParticleEffectHandle, NiagaraComp);

	Handle = ActiveParticleEffectHandle;
	ActiveParticleEffectHandle++;
	return NiagaraComp;
}

void ABaseCharacter::RemoveBuffVfx(const int Handle, const bool SpawnDetachedParticleActor)
{
	if(ActiveParticleEffects.Contains(Handle))
	{
		if(SpawnDetachedParticleActor)
		{
			const auto DetachedParticleActor = GetWorld()->SpawnActor<ADetachedParticleActor>();
			DetachedParticleActor->InitializeParticleActor(ActiveParticleEffects[Handle], this, -1);
		}
		else
		{
			ActiveParticleEffects[Handle]->DestroyComponent();
		}

		ActiveParticleEffects.Remove(Handle);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("INVALID HANDLE"));
	}
}