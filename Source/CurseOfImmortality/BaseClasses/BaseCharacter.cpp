// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "CharacterMovement.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UCharacterMovement>(TEXT("CharacterMovement"));
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	Setup();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::ReceiveDamage(float Damage)
{
	Health -= Damage;
}

void ABaseCharacter::Setup()
{
	
}

void ABaseCharacter::DealDamage(float Damage, ABaseCharacter *EnemyCharacter)
{
	EnemyCharacter->ReceiveDamage(Damage);
}

void ABaseCharacter::OnDeath()
{
	//Do stuff
}