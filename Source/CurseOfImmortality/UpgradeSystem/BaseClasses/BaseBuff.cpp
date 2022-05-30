// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuff.h"

#include "AttackManager.h"
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

void UBaseBuff::AddBuffStack()
{
	
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

	if(!InheritRotation &&ParticleSystem != nullptr)
	{
		ParticleSystem->SetWorldRotation(FRotator::ZeroRotator);
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
	//ParticleSystem = Specification->ParticleSystem;
	Stackable = Specification->Stackable;
	CustomBuffEnd = Specification->CustomBuffEnd;
	InheritRotation = Specification->InheritRotation;
	StatModifier = Specification->StatModifier;
	RefreshOnNew = Specification->RefreshOnNew;
	StatModifications = Specification->StatModifications;
}

void UBaseBuff::InitializeBuff(int Level, ABaseCharacter* _Owner)
{
	Owner = _Owner;
	RemainingDuration = BuffDuration;
}

UNiagaraComponent* UBaseBuff::SetupVfx(const EAttachmentPoint AttachmentPoint)
{
	auto VfxList = FPersistentWorldManager::AttackManager->PossibleUpgrades->BuffVFX;
	if(!VfxList.Contains(BuffType))
	{
		UE_LOG(LogTemp, Warning, TEXT("No VFX available"));
		return nullptr;
	}

	if(VfxList[BuffType] == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No VFX Asset set for Buff %s"), *DisplayName);
		return nullptr;
	}

	return Owner->SetupBuffVfx(VfxList[BuffType], AttachmentPoint, DefaultHandle);

}

void UBaseBuff::DestroyVfx()
{
	Owner->RemoveBuffVfx(DefaultHandle);
}
