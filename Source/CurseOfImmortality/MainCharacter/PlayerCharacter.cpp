// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"
#include "CurseOfImmortality/AI/AIBaseClasses/StateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"


// Sets default values
APlayerCharacter::APlayerCharacter() : ABaseCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Setup Components and attach to RootComponent
    //CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	//CapsuleComponent = static_cast<UCapsuleComponent*>(RootComponent);
	//CapsuleComponent->SetupAttachment(RootComponent);
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(CapsuleComponent);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(CapsuleComponent);
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);
	InputManager = CreateDefaultSubobject<UInputManager>(TEXT("InputManager"));
	AttackManager = CreateDefaultSubobject<UAttackManager>(TEXT("AttackManager"));
	StateMachine = CreateDefaultSubobject<UStateMachine>(TEXT("StateMachine"));
	DamageComponent = CreateDefaultSubobject<UDamageComponent>("DamageComponent");
}
 

// Called when the game starts or when spawned
void APlayerCharacter::Setup()
{
	Super::Setup();
	FPersistentWorldManager::PlayerCharacter = this;
	SetupInputComponent();
	DamageComponent->ConvertInterface();
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APlayerCharacter::ReceiveDamage(float Damage)
{
	Super::ReceiveDamage(Damage);
}

void APlayerCharacter::DealDamage(float Damage, ABaseCharacter *EnemyCharacter)
{
	Super::DealDamage(Damage, EnemyCharacter);
}

void APlayerCharacter::OnDeath()
{
	Super::OnDeath();
}


//Called to bind functionality to input
void APlayerCharacter::SetupInputComponent()
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