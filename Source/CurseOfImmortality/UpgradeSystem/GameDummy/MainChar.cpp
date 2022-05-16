// Fill out your copyright notice in the Description page of Project Settings.


#include "MainChar.h"

#include "GameController.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"

// Sets default values
AMainChar::AMainChar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttackManager = CreateDefaultSubobject<UAttackManager>("AttackManager");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMainChar::BeginPlay()
{
	Super::BeginPlay();
	BindToInput();
	static_cast<UGameController*>(GetGameInstance())->SetMainChar(this);
}

void AMainChar::BindToInput() 
{
	// Initialize our component
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		// Bind inputs here
		// InputComponent->BindAction("Jump", IE_Pressed, this, &AUnrealisticPawn::Jump);
		// etc...

		InputComponent->BindAction("TestInputMelee", IE_Pressed, this, &AMainChar::OnMeleeKeyPressed);	
		InputComponent->BindAction("TestInputRanged", IE_Pressed, this, &AMainChar::OnRangedKeyPressed);	
		InputComponent->BindAction("testInputSpecial", IE_Pressed, this, &AMainChar::OnSpecialKeyPressed);	

		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}


// Called every frame
void AMainChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainChar::OnMeleeKeyPressed()
{
	AttackManager->OnKeyPressed(Melee);
}

void AMainChar::OnRangedKeyPressed()
{
	AttackManager->OnKeyPressed(Ranged);
}

void AMainChar::OnSpecialKeyPressed()
{
	AttackManager->OnKeyPressed(Special);
}



