#include "CurseOfImmortality/BaseClasses/InvisibleWalls.h"

#include "CurseOfImmortality/AI/AIBaseClasses/BaseEnemyPawn.h"

// Sets default values
AInvisibleWalls::AInvisibleWalls()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("Wall");
	CollisionBox->SetupAttachment(RootComponent);
}

void AInvisibleWalls::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AInvisibleWalls::OnOverlapEnd);
}

void AInvisibleWalls::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABaseEnemyPawn* Enemy = Cast<ABaseEnemyPawn>(OtherActor))
	{
		Enemy->StartGatePassed = true;
	}
}
