// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"

UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	for (const auto Tuple : DamagingComponents)
	{
		if(Tuple.Value != nullptr)
		{
			Tuple.Value->Tick(DeltaTime);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("DamageObject is null (Tick)"));
		}
	}
}

void UDamageComponent::ConvertInterface()
{
	for (int i = 0; i < References.Num(); ++i)
	{
		const auto Component = References[i].GetComponent(GetOwner());
		if(Component == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is not the name of a component on this actor!"), *References[i].ComponentProperty.ToString());
			continue;
		}

		auto Primitive = static_cast<UPrimitiveComponent*>(Component);

		if(Primitive == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s does not reference a Primitive Component"));
			continue;
		}
		auto DamageObject = FPersistentWorldManager::ObjectFactory->GetDamageObject(DamageObjects[i]);
		DamagingComponents.Add(Primitive, DamageObject);
	}
	UE_LOG(LogTemp, Warning, TEXT("Converted %i of %i References to DamagingComponents"), DamagingComponents.Num(), References.Num());
}

void UDamageComponent::OnCharacterHit(const UPrimitiveComponent* DamageComponentOverlap, ABaseCharacter* HitCharacter)
{
	if(!DamagingComponents.Contains(DamageComponentOverlap))
	{
		UE_LOG(LogTemp, Warning, TEXT("The Hitbox is not contained"));
		return;
	}

	if(DamagingComponents[DamageComponentOverlap] == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageComponent is null!"));
		return;
	}

	DamagingComponents[DamageComponentOverlap]->DealDamage(HitCharacter);
	//HitCharacter->TakeDmg(DamagingComponents[DamageComponentOverlap]->Damage, nullptr, nullptr, true);
}

void UDamageComponent::SetupDamageComponent(UPrimitiveComponent* Component, UDamageObject* DamageObject)
{
	/*
	if(DamagingComponents.Contains(Component))
	{
		DamagingComponents[Component] = DamageObject;
	}
	else
	{
		DamagingComponents.Add(Component, DamageObject);
	}
	*/
}

void UDamageComponent::ResetAllHitCharacters()
{
	for (auto Tuple : DamagingComponents)
	{
		if(Tuple.Value != nullptr)
		{
			Tuple.Value->HitCharacters.Empty();			
		}
	}
}
