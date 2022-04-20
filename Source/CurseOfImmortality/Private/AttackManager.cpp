// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackManager.h"

// Sets default values
AAttackManager::AAttackManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAttackManager::BeginPlay()
{
	Super::BeginPlay();
	BindToInput();
	
}

// Called every frame
void AAttackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//printf("?????");
	//UE_LOG(LogTemp, Warning, TEXT("Test"));


}

void AAttackManager::BindToInput() 
{
	// Initialize our component
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		// Bind inputs here
		// InputComponent->BindAction("Jump", IE_Pressed, this, &AUnrealisticPawn::Jump);
		// etc...
		InputComponent->BindAction("TestInputZ", IE_Pressed, this, &AAttackManager::OnKeyPressed);	

		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());

	}

}

void AAttackManager::OnKeyPressed()
{
	
	//ABaseAbility* baseAbilityInstance = (ABaseAbility*) GetWorld()->SpawnActor(ABaseAbility::StaticClass());
	ABaseAbility* baseAbilityInstance = (ABaseAbility*) GetWorld()->SpawnActor(abilityClassType);
	//UWorld::SpawnActor(abilityClassType);
	//UE_LOG(LogTemp, Warning, TEXT("Keypress was registered"));
}

