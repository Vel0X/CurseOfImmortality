// 


#include "Arrow.h"

#include "NiagaraComponent.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"


// Sets default values
AArrow::AArrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	ArrowPivot = CreateDefaultSubobject<USceneComponent>("ArrowPivot");
	ArrowPivot->SetupAttachment(RootComponent);
	
	Arrow = CreateDefaultSubobject<UNiagaraComponent>("Arrow");
	Arrow->SetupAttachment(ArrowPivot);
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	Pc = FPersistentWorldManager::PlayerCharacter;
	
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Pc = FPersistentWorldManager::PlayerCharacter;

	if(!Pc || FPersistentWorldManager::MawOfSothros)
	{
		Arrow->SetVisibility(false);
		return;
	}

	auto Round = FPersistentWorldManager::RoundsManager->ActiveRound;

	if(!Round)
	{
		Arrow->SetVisibility(false);
		return;
	}
	TArray<ABaseEnemyPawn*> Enemies;
	const int Count = Round->GetRemainingEnemies(Enemies);
	if(Count == 0 || Count > 3)
	{
		Arrow->SetVisibility(false);
		return;
	}

	int ClosestIndex = -1;
	float ClosestDistance = 1000000.0f;
	const FVector ActorLocation = Pc->GetActorLocation();
	SetActorLocation(ActorLocation);


	for (int i = 0; i < Enemies.Num(); ++i)
	{
		if(!Enemies[i])
		{
			UE_LOG(LogTemp, Warning, TEXT("ENEMY WAS NULL"));
			continue;
		}
		
		const float Distance = FVector::Distance(Enemies[i]->GetActorLocation(), ActorLocation);
		
		if(Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestIndex = i;
		}
	}

	if(ClosestIndex == -1)
	{
		Arrow->SetVisibility(false);
		return;
	}

	Arrow->SetVisibility(true);

	const FVector EnemyLocation =  Enemies[ClosestIndex]->GetActorLocation();
	FVector Dir = EnemyLocation - ActorLocation;
	Dir.Z = 0;
	Dir.Normalize();
	ArrowPivot->SetWorldRotation(Dir.Rotation());
}


