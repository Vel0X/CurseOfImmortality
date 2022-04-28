// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Setup Components and attach to RootComponent
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(CapsuleComponent);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(CapsuleComponent);
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);
	InputManager = CreateDefaultSubobject<UInputManager>(TEXT("InputManager"));
}


// Called when the game starts or when spawned
void APlayerCharacter::Setup()
{
	Super::Setup();
	SetupPlayerInputComponent();
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


//Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent()
{
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputManager->SetupPlayerInput(InputComponent);

		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

/*void APlayerCharacter::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);

}

void APlayerCharacter::DoDamage(float Damage, ABaseCharacter EnemyCharacter)
{
	Super::DoDamage(Damage, EnemyCharacter);

}

void APlayerCharacter::OnDeath()
{
	//Do stuff

}*/
