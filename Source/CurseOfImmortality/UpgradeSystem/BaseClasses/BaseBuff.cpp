﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuff.h"

#include "BaseAbility.h"
#include "NiagaraComponent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "DataAssets/BuffSpecification.h"

UBaseBuff::UBaseBuff()
{
}

void UBaseBuff::OnTakeDamage(ABaseAbility* Ability)
{
}

void UBaseBuff::OnDealDamage(float Amount, ABaseCharacter* Recipient)
{
	
}

bool UBaseBuff::AddBuffStack()
{
	if(RefreshOnNew)
	{
		RemainingDuration = BuffDuration;
	}
	
	//can not add another stack
	if(CurrentStacks >= MaxStacks)
	{
		return false;
	}
	
	CurrentStacks++;

	if(StatModifier)
	{
		for (const auto Tuple : StatModifications)
		{
			const auto Stat = Tuple.Key;
			StatModifications[Stat] += StatModificationsPerStack[Stat];
		}
	}
	
	return true;
}

void UBaseBuff::OnBuffBegin()
{
	
}


void UBaseBuff::OnBuffTick(float DeltaTime)
{
	if(!CustomBuffEnd)
	{
		if(RemainingDuration <= 0.0f)
		{
			Owner->RemoveBuff(this);
		}
		RemainingDuration -= DeltaTime;
	}

	if(!InheritRotation &&ParticleSystemComponent != nullptr)
	{
		ParticleSystemComponent->SetWorldRotation(FRotator::ZeroRotator);
	}
	
}

void UBaseBuff::OnBuffEnd()
{
	
}

void UBaseBuff::SetupBuff(UBuffSpecification* Specification)
{
	DisplayName = Specification->DisplayName;
	BuffType = Specification->BuffType;
	BuffDuration = Specification->BuffDuration;
	ParticleSystem = Specification->ParticleSystem;
	Stackable = Specification->Stackable;
	MaxStacks = Specification->MaxStacks;
	CustomBuffEnd = Specification->CustomBuffEnd;
	InheritRotation = Specification->InheritRotation;
	StatModifier = Specification->StatModifier;
	RefreshOnNew = Specification->RefreshOnNew;
	StatModificationsPerStack = Specification->StatModifications; //initially the buff has one stack
	StatModifications = Specification->StatModifications;
}

void UBaseBuff::InitializeBuff(int Level, ABaseCharacter* _Owner, ABaseCharacter* _Inflicter)
{
	BuffLevel = Level;
	Owner = _Owner;
	Inflicter = _Inflicter;
	RemainingDuration = BuffDuration;
}

UNiagaraComponent* UBaseBuff::SetupVfx(const EAttachmentPoint AttachmentPoint)
{
	if(ParticleSystem == nullptr)
	{
		return nullptr;
	}

	return Owner->SetupBuffVfx(ParticleSystem, AttachmentPoint, DefaultHandle);
}

void UBaseBuff::DestroyVfx()
{
	Owner->RemoveBuffVfx(DefaultHandle);
}
