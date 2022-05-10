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
	LastAction = InputAction::NoAction;
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
	
	if (Player->CurrentAnimationDuration > 0)
	{
		Player->CurrentAnimationDuration -= DeltaTime;
	//	UE_LOG(LogTemp, Warning, TEXT("Text,%f"), Player->CurrentAnimationDuration);
		
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
	if (Value != 0 && LastAction == InputAction::NoAction)
	{
		LastAction = InputAction::Running;
	}
	MoveInput.X = Value;
	MovementComponent->SetDirection(MoveInput, Player->MovementSpeed);
}

void UInputManager::MoveRight(float Value)
{
	if (Value != 0 && LastAction == InputAction::NoAction)
	{
		LastAction = InputAction::Running;
	}
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

/*void UInputManager::SetAction(InputAction Action)
{
	if(LastAction != )
	LastAction = Action;
}*/

void UInputManager::AddToBuffer(InputAction _InputAction)
{
	if(Player->CurrentAnimationDuration <= 0 && InputBuffer.Num() == 0)
	{
		DoAction(_InputAction);
	} else if (Player->CurrentAnimationDuration <= MaxBufferTime)
	{
		InputBuffer.Add(_InputAction);
		UE_LOG(LogTemp, Display, TEXT("Added Action to buffer"));
	}
}

void UInputManager::DoAction(InputAction _InputAction)
{
	UE_LOG(LogTemp, Display, TEXT("Used Action"));
	switch (_InputAction)
	{
	case InputAction::MeleeAbility:
		LastAction = InputAction::MeleeAbility;
		//static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnMeleeKeyPressed();
		break;
	case InputAction::RangedAbility:
		LastAction = InputAction::RangedAbility;
		static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnRangedKeyPressed();
		break;
	case InputAction::SpecialAbility:
		LastAction = InputAction::SpecialAbility;
		static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnSpecialKeyPressed();
		break;
	case InputAction::Dash:
		LastAction = InputAction::Dash;
		//static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnDashKeyPressed();
		break;
	default:
		break;
	}
}