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
		AddBuffParticles(Buff);
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
		RemoveBuffParticles(Buff);
		if(Buff->StatModifier)
		{
			RecalculateStats();
		}
	}
}

void AChar::AddBuffParticles(UBaseBuff* Buff)
{
	if(!ActiveParticleEffects.Contains(Buff->BuffType))
	{
		auto FX = static_cast<UGameController*>(GetGameInstance())->GetAttackManager()->PossibleUpgrades->BuffVFX;
		if(!FX.Contains(Buff->BuffType))
		{
			UE_LOG(LogTemp, Warning, TEXT("No VFX available"));
			return;
		}
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(FX[Buff->BuffType], RootComponent, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
		NiagaraComp->SetupAttachment(RootComponent);
		ActiveParticleEffects.Add(Buff->BuffType, NiagaraComp);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VFX already exists"));
	}
}

void AChar::RemoveBuffParticles(const UBaseBuff* Buff)
{
	if(ActiveParticleEffects.Contains(Buff->BuffType))
	{
		const auto DetachedParticleActor = GetWorld()->SpawnActor<ADetachedParticleActor>();
		DetachedParticleActor->InitializeParticleActor(ActiveParticleEffects[Buff->BuffType], nullptr, -1);
		ActiveParticleEffects.Remove(Buff->BuffType);
	}

}

void AChar::TakeDmg(float Amount, bool Verbose)
{
	CurrentHealth -= Amount;
	if(Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("After Take Damage: Char Health is at %f Max Health %f"), CurrentHealth, Stats[Health]);
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


