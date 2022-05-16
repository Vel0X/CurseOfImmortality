// Fill out your copyright notice in the Description page of Project Settings.


#include "Char.h"

#include "GameController.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/BaseStatSpecification.h"
#include "CurseOfImmortality/UpgradeSystem/Utility/DetachedParticleActor.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"

// Sets default values
AChar::AChar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	UpperAttachmentPoint = CreateDefaultSubobject<USceneComponent>("UpperAttachmentPoint");
	UpperAttachmentPoint->SetupAttachment(RootComponent);
	CenterAttachmentPoint = CreateDefaultSubobject<USceneComponent>("CenterAttachmentPoint");
	CenterAttachmentPoint->SetupAttachment(RootComponent);
	LowerAttachmentPoint = CreateDefaultSubobject<USceneComponent>("LowerAttachmentPoint");
	LowerAttachmentPoint->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AChar::BeginPlay()
{
	Super::BeginPlay();
	RecalculateStats();
	if(Stats.Contains(Health))
	{
		CurrentHealth = Stats[Health];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("!!!"));
	}
	
}

// Called every frame
void AChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (int i = Buffs.Num() - 1; i >= 0; --i)
	{
		Buffs[i]->OnBuffTick(DeltaTime);

	}
}

void AChar::RecalculateStats()
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

void AChar::AddBuff(UBaseBuff* Buff)
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

void AChar::RemoveBuff(UBaseBuff* Buff)
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

void AChar::TakeDmg(float Amount, AChar* Dealer, ABaseAbility* Ability, bool Verbose)
{
	CurrentHealth -= Amount;
	if(Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("After Take Damage: Char Health is at %f Max Health %f"), CurrentHealth, Stats[Health]);
	}


	//notify all buffs of the damage taken
	
	for (int i = 0; i < Buffs.Num(); ++i)
	{
		Buffs[i]->OnTakeDamage(Ability);
	}
	
}

void AChar::Heal(float Amount, bool Verbose)
{
	CurrentHealth += Amount;
	if(CurrentHealth > Stats[Health])
	{
		CurrentHealth = Stats[Health];
	}

	if(Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("After Heal: Char Health is at %f Max Health %f"), CurrentHealth, Stats[Health]);
	}
}

UNiagaraComponent* AChar::SetupBuffVfx(UNiagaraSystem* Vfx, const EAttachmentPoint AttachmentPoint, int& Handle)
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

void AChar::RemoveBuffVfx(const int Handle, const bool SpawnDetachedParticleActor)
{
	if(ActiveParticleEffects.Contains(Handle))
	{
		if(SpawnDetachedParticleActor)
		{
			const auto DetachedParticleActor = GetWorld()->SpawnActor<ADetachedParticleActor>();
			DetachedParticleActor->InitializeParticleActor(ActiveParticleEffects[Handle], nullptr, -1);
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