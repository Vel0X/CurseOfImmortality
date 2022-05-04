// Fill out your copyright notice in the Description page of Project Settings.


#include "InputManager.h"
#include "PlayerCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"


// Sets default values for this component's properties
UInputManager::UInputManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxBufferTime = 0.5;
	TimeTillNextAction = 0;
	Player = static_cast <APlayerCharacter*>(GetOwner());
	if(Player != nullptr)
	{
		MovementComponent = Player->MovementComponent;
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is Null"));
	}
}


// Called when the game starts
void UInputManager::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UInputManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (TimeTillNextAction > 0)
	{
		TimeTillNextAction -= DeltaTime;
	} else if (InputBuffer.Num()>0)
	{
		DoAction(InputBuffer.Last());
		InputBuffer.Empty();
	}
	
}

//Called to bind functionality to input
void UInputManager::SetupPlayerInput(UInputComponent* InputComponent)
{
	InputComponent->BindAxis("MoveForward", this, &UInputManager::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &UInputManager::MoveRight);
	InputComponent->BindAction("MeleeAbility",  IE_Pressed, this, &UInputManager::MeleeAbility);
	InputComponent->BindAction("RangedAbility",  IE_Pressed, this, &UInputManager::RangedAbility);
	InputComponent->BindAction("SpecialAbility",  IE_Pressed, this, &UInputManager::SpecialAbility);
	InputComponent->BindAction("Dash",  IE_Pressed, this, &UInputManager::Dash);
}

void UInputManager::MoveForward(float Value)
{
	MoveInput.X = Value;
	MovementComponent->SetDirection(MoveInput, Player->MovementSpeed);
}

void UInputManager::MoveRight(float Value)
{
	MoveInput.Y = Value;
	MovementComponent->SetDirection(MoveInput, Player->MovementSpeed);
}

void UInputManager::MeleeAbility()
{
	AddToBuffer(InputAction::MeleeAbility);
}

void UInputManager::RangedAbility()
{
	AddToBuffer(InputAction::RangedAbility);
}

void UInputManager::SpecialAbility()
{
	AddToBuffer(InputAction::SpecialAbility);
}

void UInputManager::Dash()
{
	AddToBuffer(InputAction::Dash);
}

void UInputManager::AddToBuffer(InputAction _InputAction)
{
	if(TimeTillNextAction <= 0 && InputBuffer.Num() == 0)
	{
		DoAction(_InputAction);
	} else if (TimeTillNextAction <= MaxBufferTime)
	{
		InputBuffer.Add(_InputAction);
		UE_LOG(LogTemp, Display, TEXT("Added Action to buffer"));
	}
}

void UInputManager::DoAction(InputAction _InputAction)
{
	TimeTillNextAction = 1.5; //Set to Ability time
	UE_LOG(LogTemp, Display, TEXT("Used Action"));
	switch (_InputAction)
	{
	case InputAction::MeleeAbility:
		//static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnMeleeKeyPressed();
		break;
	case InputAction::RangedAbility:
		static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnRangedKeyPressed();
		break;
	case InputAction::SpecialAbility:
		static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnSpecialKeyPressed();
		break;
	case InputAction::Dash:
		//static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnDashKeyPressed();
		break;
	}
}