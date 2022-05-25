// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDamageObject.h"

#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UAIDamageObject::UAIDamageObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DamageSphere = CreateDefaultSubobject<USphereComponent>("DamageSphere");
}

// Called when the game starts
void UAIDamageObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UAIDamageObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (SetupComplete)
	{
		if (NoDot)
		{
			DealDamageToPawns();
			DestroyComponent();
		}
		else
		{
			DealDamageToPawns();
			if (Duration <= 0)
			{
				DestroyComponent();
			}
			Duration -= DeltaTime;
		}
	}
}

void UAIDamageObject::DealDamageToPawns() const
{
	TArray<AActor*> OverlappingActors;
	DamageSphere->GetOverlappingActors(OverlappingActors);

	//UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"),
	//       ( OverlappingActors.IsEmpty() ? TEXT("true") : TEXT("false") ));
	// UE_LOG(LogTemp, Warning, TEXT("%f"), DamageSphere->GetUnscaledSphereRadius());
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *DamageSphere->GetComponentLocation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("%s"), DamageSphere->GetCollisionEnabled());
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *DamageSphere->GetCollisionProfileName().ToString());

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (ABaseCharacter* OtherPawn = Cast<ABaseCharacter>(OverlappingActor))
		{
			ABaseCharacter* SelfRef = Cast<ABaseCharacter>(GetOwner());
			//SelfRef->DealDamage(Damage, OtherPawn);
			UE_LOG(LogTemp, Warning, TEXT("Damage Dealt"))
		}
	}
}

void UAIDamageObject::SetUp(const float _Duration, const bool bNoDot, const float _DamageRadius,
                            const FVector _SpawnLocation,
                            const float _Damage)
{
	this->Duration = _Duration;
	this->NoDot = bNoDot;
	this->DamageRadius = _DamageRadius;
	this->SpawnLocation = _SpawnLocation;
	this->Damage = _Damage;

	DamageSphere->SetSphereRadius(_DamageRadius);
	DamageSphere->SetWorldLocation(_SpawnLocation);
	DrawDebugSphere(GetWorld(), _SpawnLocation, _DamageRadius, 20, FColor::Red, false, Duration);
	SetupComplete = true;
}
