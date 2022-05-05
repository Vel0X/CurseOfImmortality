// Fill out your copyright notice in the Description page of Project Settings.


#include "Char.h"

#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/BaseStatSpecification.h"


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
	Buffs.Add(Buff);
	if(Buff->StatModifier)
	{
		RecalculateStats();
	}
	Buff->IntitializeBuff(1,this);
	UE_LOG(LogTemp, Warning, TEXT("Buff was added"));
}

void AChar::RemoveBuff(UBaseBuff* Buff)
{
	if(Buffs.Contains(Buff))
	{
	UE_LOG(LogTemp, Warning, TEXT("Buff was removed"));
		Buffs.Remove(Buff);
		if(Buff->StatModifier)
		{
			RecalculateStats();
		}
	}
	
}

void AChar::TakeDamage(float Amount, bool Verbose)
{
	CurrentHealth -= Amount;
	if(Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("Char Health is at %f Max Health %f"), CurrentHealth, Stats[Health]);
	}
}

