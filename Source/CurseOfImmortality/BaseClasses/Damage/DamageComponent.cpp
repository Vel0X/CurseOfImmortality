// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "CurseOfImmortality/UpgradeSystem/Utility/DetachedParticleActor.h"

UDamageComponent::UDamageComponent()
{
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
		if (Tuple.Value != nullptr)
		{
			Tuple.Value->Tick(DeltaTime);
		}
		else
		{
			if (FPersistentWorldManager::GetLogLevel(DamageComponent))
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
		if (Component == nullptr)
		{
			if (FPersistentWorldManager::GetLogLevel(DamageComponent))
				UE_LOG(LogTemp, Warning, TEXT("%s is not the name of a component on this actor!"),
			       *DamagingHitboxReferences[i].ComponentProperty.ToString());
			continue;
		}

		auto Primitive = Cast<UPrimitiveComponent>(Component);

		if (Primitive == nullptr)
		{
			if (FPersistentWorldManager::GetLogLevel(DamageComponent))
				UE_LOG(LogTemp, Warning, TEXT("%s does not reference a Primitive Component"));
			continue;
		}
		auto DamageObject = FPersistentWorldManager::ObjectFactory->GetDamageObject(
			DamagingHitboxDamageSpecifications[i]);
		SetDamageObjectOwner(DamageObject);
		DamagingHitboxes.Add(Primitive, DamageObject);
	}

	if (FPersistentWorldManager::GetLogLevel(DamageComponent))
		UE_LOG(LogTemp, Warning, TEXT("Converted %i of %i References to DamagingComponents"), DamagingHitboxes.Num(),
	       DamagingHitboxReferences.Num());

	for (int i = 0; i < DirectDamageSpecifications.Num(); ++i)
	{
		auto DamageObject = FPersistentWorldManager::ObjectFactory->GetDamageObject(DirectDamageSpecifications[i]);
		SetDamageObjectOwner(DamageObject);
		DirectDamageObjects.Add(DamageObject);
	}
}

bool UDamageComponent::OnCharacterHit(const UPrimitiveComponent* DamageComponentOverlap, ABaseCharacter* HitCharacter, UPrimitiveComponent* BodyHitbox)
{
	if (!DamagingHitboxes.Contains(DamageComponentOverlap))
	{
		if (FPersistentWorldManager::GetLogLevel(DamageComponent))
			UE_LOG(LogTemp, Warning, TEXT("The Hitbox is not contained"));
		return false;
	}

	if (DamagingHitboxes[DamageComponentOverlap] == nullptr)
	{
		if (FPersistentWorldManager::GetLogLevel(DamageComponent))
			UE_LOG(LogTemp, Warning, TEXT("DamageComponent is null!"));
		return false;
	}

	auto DamageObject = DamagingHitboxes[DamageComponentOverlap];
	bool Hit = DamageObject->DealDamage(HitCharacter);
	if(Hit && BodyHitbox && DamageObject->HitVfx)
	{
		const FVector SpawnLocation =BodyHitbox->GetComponentLocation();

		const auto DetachedParticleActor = GetWorld()->SpawnActor<ADetachedParticleActor>();
		DetachedParticleActor->InitializeParticleActor(SpawnLocation, DamageObject->HitVfx, nullptr, 0.8f);
	}
	return Hit;
}

void UDamageComponent::DirectCharacterHit(int Index, ABaseCharacter* HitCharacter)
{
	DirectDamageObjects[Index]->DealDamage(HitCharacter);
}

void UDamageComponent::SetupDamagingComponentByDamageObject(UPrimitiveComponent* Component, UDamageObject* DamageObject)
{
	SetDamageObjectOwner(DamageObject);
	if (!DamagingHitboxes.Contains(Component))
	{
		UE_LOG(LogTemp, Error, TEXT("Damaging Hitboxes does not contain DamageComponent"));
		return;
	}

	DamagingHitboxes[Component] = DamageObject;
}

void UDamageComponent::SetupDamagingComponentByDamageSpecification(UPrimitiveComponent* Component,
                                                                   UDamageSpecification* DamageSpecification)
{
	auto DamageObject = FPersistentWorldManager::ObjectFactory->GetDamageObject(DamageSpecification);
	SetDamageObjectOwner(DamageObject);

	if (!DamagingHitboxes.Contains(Component))
	{
		UE_LOG(LogTemp, Error, TEXT("Damaging Hitboxes does not contain DamageComponent"));
		return;
	}

	DamagingHitboxes[Component] = DamageObject;
}

void UDamageComponent::SetupDamagingComponentByIndexAndDamageSpecification(int Index,
                                                                           UDamageSpecification* DamageSpecification)
{
	TArray<UPrimitiveComponent*> Keys;
	DamagingHitboxes.GetKeys(Keys);

	if (Index >= Keys.Num() || Index < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Index into DamagingHitboxes was out of Bounds"));
		return;
	}

	auto DamageObject = FPersistentWorldManager::ObjectFactory->GetDamageObject(DamageSpecification);
	SetDamageObjectOwner(DamageObject);

	DamagingHitboxes[Keys[Index]] = DamageObject;
}

void UDamageComponent::ResetAllHitCharacters()
{
	for (auto Tuple : DamagingHitboxes)
	{
		if (Tuple.Value != nullptr)
		{
			Tuple.Value->HitCharacters.Empty();
		}
	}
}

void UDamageComponent::ResetHitCharactersForHitbox(UPrimitiveComponent* Hitbox)
{
	if (DamagingHitboxes.Contains(Hitbox))
	{
		DamagingHitboxes[Hitbox]->HitCharacters.Empty();
	}
}

void UDamageComponent::ResetHitCharactersForHitboxByIndex(int Index)
{
	TArray<UPrimitiveComponent*> Keys;
	DamagingHitboxes.GetKeys(Keys);

	if (Index >= Keys.Num() || Index < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Index into DamagingHitboxes was out of Bounds"));
		return;
	}

	DamagingHitboxes[Keys[Index]]->HitCharacters.Empty();
}

void UDamageComponent::ToggleHitbox(UPrimitiveComponent* Hitbox)
{
	if (DamagingHitboxes.Contains(Hitbox))
	{
		Hitbox->SetGenerateOverlapEvents(!Hitbox->GetGenerateOverlapEvents());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Tried to toggle Hitbox that is not registered in DamageComponent!"));
	}
}

void UDamageComponent::ToggleHitboxByIndex(int Index)
{
	TArray<UPrimitiveComponent*> Keys;
	DamagingHitboxes.GetKeys(Keys);

	if (Index >= Keys.Num() || Index < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Index into DamagingHitboxes was out of Bounds"));
		return;
	}

	Keys[Index]->SetGenerateOverlapEvents(!Keys[Index]->GetGenerateOverlapEvents());
}

void UDamageComponent::SetDamageObjectOwner(UDamageObject* DamageObject) const
{
	ABaseAbility* OwningAbility = Cast<ABaseAbility>(GetOwner());
	if (OwningAbility != nullptr)
	{
		DamageObject->DamagingAbility = OwningAbility;
		DamageObject->OwningChar = OwningAbility->Caster;
	}
	else
	{
		ABaseCharacter* OwningChar = Cast<ABaseCharacter>(GetOwner());
		DamageObject->OwningChar = OwningChar;
	}
}
