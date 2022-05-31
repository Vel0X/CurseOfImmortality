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
	for (const auto Tuple : DamagingHitboxes)
	{
		if(Tuple.Value != nullptr)
		{
			Tuple.Value->Tick(DeltaTime);
		}
		else
		{
			if(FPersistentWorldManager::GetLogLevel(DamageComponent))
				UE_LOG(LogTemp, Warning, TEXT("DamageObject is null (Tick)"));
		}
	}
}

void UDamageComponent::ConvertInterface()
{

	//convert all the HitboxReferences into actual component references and initialize all the DamageObjects using the ObjectFactory and the DamageSpecification
	for (int i = 0; i < DamagingHitboxReferences.Num(); ++i)
	{
		const auto Component = DamagingHitboxReferences[i].GetComponent(GetOwner());
		if(Component == nullptr)
		{
			if(FPersistentWorldManager::GetLogLevel(DamageComponent))
				UE_LOG(LogTemp, Warning, TEXT("%s is not the name of a component on this actor!"), *DamagingHitboxReferences[i].ComponentProperty.ToString());
			continue;
		}

		auto Primitive = static_cast<UPrimitiveComponent*>(Component);

		if(Primitive == nullptr)
		{
			if(FPersistentWorldManager::GetLogLevel(DamageComponent))
				UE_LOG(LogTemp, Warning, TEXT("%s does not reference a Primitive Component"));
			continue;
		}
		auto DamageObject = FPersistentWorldManager::ObjectFactory->GetDamageObject(DamagingHitboxDamageSpecifications[i]);

		ABaseAbility* OwningAbility = Cast<ABaseAbility>(GetOwner());
		if(OwningAbility != nullptr)
		{
			DamageObject->DamagingAbility = OwningAbility;
			DamageObject->OwningChar = OwningAbility->Caster;
		}
		else
		{
			ABaseCharacter* OwningChar = Cast<ABaseCharacter>(GetOwner());
			DamageObject->OwningChar = OwningChar;
		}
		
		DamagingHitboxes.Add(Primitive, DamageObject);
	}

	if(FPersistentWorldManager::GetLogLevel(DamageComponent))
		UE_LOG(LogTemp, Warning, TEXT("Converted %i of %i References to DamagingComponents"), DamagingHitboxes.Num(), DamagingHitboxReferences.Num());

	for (int i = 0; i < DirectDamageSpecifications.Num(); ++i)
	{
		auto DamageObject = FPersistentWorldManager::ObjectFactory->GetDamageObject(DirectDamageSpecifications[i]);

		ABaseAbility* OwningAbility = Cast<ABaseAbility>(GetOwner());
		if(OwningAbility != nullptr)
		{
			DamageObject->DamagingAbility = OwningAbility;
			DamageObject->OwningChar = OwningAbility->Caster;
		}
		else
		{
			ABaseCharacter* OwningChar = Cast<ABaseCharacter>(GetOwner());
			DamageObject->OwningChar = OwningChar;
		}
		
		DirectDamageObjects.Add(DamageObject);
	}
}

bool UDamageComponent::OnCharacterHit(const UPrimitiveComponent* DamageComponentOverlap, ABaseCharacter* HitCharacter)
{
	if(!DamagingHitboxes.Contains(DamageComponentOverlap))
	{
		if(FPersistentWorldManager::GetLogLevel(DamageComponent))
			UE_LOG(LogTemp, Warning, TEXT("The Hitbox is not contained"));
		return false;
	}

	if(DamagingHitboxes[DamageComponentOverlap] == nullptr)
	{
		if(FPersistentWorldManager::GetLogLevel(DamageComponent))
			UE_LOG(LogTemp, Warning, TEXT("DamageComponent is null!"));
		return false;
	}

	return DamagingHitboxes[DamageComponentOverlap]->DealDamage(HitCharacter);
	//HitCharacter->TakeDmg(DamagingComponents[DamageComponentOverlap]->Damage, nullptr, nullptr, true);
}

void UDamageComponent::DirectCharacterHit(int Index, ABaseCharacter* HitCharacter)
{
	DirectDamageObjects[Index]->DealDamage(HitCharacter);
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
	for (auto Tuple : DamagingHitboxes)
	{
		if(Tuple.Value != nullptr)
		{
			Tuple.Value->HitCharacters.Empty();			
		}
	}
}

void UDamageComponent::ToggleHitbox(UPrimitiveComponent* Hitbox)
{
	if(DamagingHitboxes.Contains(Hitbox))
	{
		Hitbox->SetGenerateOverlapEvents(!Hitbox->GetGenerateOverlapEvents());
	}
	else
	{
		if(FPersistentWorldManager::GetLogLevel(DamageComponent))
			UE_LOG(LogTemp, Warning, TEXT("Toggled Hitbox, that is not registered in DamageComponent!"));
	}
}
