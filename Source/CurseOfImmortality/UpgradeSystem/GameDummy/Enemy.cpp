// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "GameController.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	TimeUntilNextShot = ShootInterval;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	static_cast<UGameController*>(GetGameInstance())->AddEnemy(this);
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(TimeUntilNextShot <= 0.0f)
	{
		CastAbility();
		TimeUntilNextShot = ShootInterval;
	}
	else
	{
		TimeUntilNextShot -= DeltaTime;
	}

}

void AEnemy::CastAbility()
{
	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();
	
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(Specification->Class, &Location, &Rotation));
	AbilityInstance->InitializeAbility(0, this, 1);
	AbilityInstance->OnAbilityCreation();
	AbilityInstance->AfterInitialization();
}

