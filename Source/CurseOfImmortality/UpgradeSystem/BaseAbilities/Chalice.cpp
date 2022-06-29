// 


#include "Chalice.h"

#include "NiagaraComponent.h"


// Sets default values
AChalice::AChalice()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Vfx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileMesh"));
	Vfx->SetupAttachment(RootComponent);
	
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AChalice::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChalice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(CurrentCooldown > 0.0f)
	{
		CurrentCooldown -= DeltaTime;
		if(CurrentCooldown <= 0.0f)
		{
			Vfx->Activate();
		}
	}
}

void AChalice::OnHitNotify(ABaseCharacter* HitCharacter)
{
	Super::OnHitNotify(HitCharacter);
	if(CurrentCooldown <= 0.0f)
	{
		//Add Heal Buff to Player
		CurrentCooldown = Cooldown;
		Vfx->Deactivate();
	}
	
}

