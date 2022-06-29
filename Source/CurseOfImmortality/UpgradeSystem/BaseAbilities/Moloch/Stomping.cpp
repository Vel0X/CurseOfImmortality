#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/Moloch/Stomping.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

AStomping::AStomping()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("Vfx");
	ParticleSystem->SetupAttachment(RootComponent);

	Collider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	Collider->SetupAttachment(RootComponent);
}

void AStomping::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (DamageWindow <= 0.f)
	{
		Collider->SetGenerateOverlapEvents(false);
	}
	DamageWindow -= DeltaSeconds;
}
