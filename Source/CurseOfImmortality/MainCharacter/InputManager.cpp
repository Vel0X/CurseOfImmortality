// Fill out your copyright notice in the Description page of Project Settings.


#include "InputManager.h"
#include "PlayerAnim.h"
#include "PlayerCharacter.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "CurseOfImmortality/BaseClasses/CharacterMovement.h"


// Sets default values for this component's properties
UInputManager::UInputManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxBufferTime = 0.3;
	LastAction = InputAction::NoAction;

	
	Player = Cast<APlayerCharacter>(GetOwner());
	
	if(Player != nullptr)
	{
		MovementComponent = Player->MovementComponent;

		if(MovementComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("MovementComponent is NULL!!!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is Null"));
	}
}


// Called when the game starts
void UInputManager::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<APlayerCharacter>(GetOwner());
	if(Player != nullptr)
	{
		MovementComponent = Player->MovementComponent;
		if(MovementComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("MovementComponent is Null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is Null"));
	}
}

// Called every frame
void UInputManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!MoveLock)
	{
		if(Player->PlayerAnim->Idle || Player->PlayerAnim->Melee || Player->PlayerAnim->Running)
		{
			if (MoveX != 0 && LastAction == InputAction::NoAction || MoveY != 0 && LastAction == InputAction::NoAction)
			{
				LastAction = InputAction::Running;
				Move();
				Stopped = false;
			} else
			{
				if (MoveX != 0 || MoveY != 0)
				{
					Move();
					Stopped = false;
				} else
				{
					//To stop only once unless reset
					if(!Stopped)
					{
						if(MoveX == 0 && MoveY == 0)
						{
							Move();
							Stopped = true;
							LastAction = InputAction::NoAction;
						}
					}
				}
			}
		}
	}
	
	
	if (Player->CurrentDashCooldown > 0)
	{
		Player->CurrentDashCooldown -= DeltaTime;
	}
	
	if (Player->CurrentMeleeFollowUpTime > 0)
	{
		Player->CurrentMeleeFollowUpTime -= DeltaTime;
	}
	else if (Player->CurrentMeleeFollowUpTime <= 0 && Player->MeleeComboCount != 0)
	{
		Player->MeleeComboCount = 0;
		Player->MeleeStartFrame = 0;
	}
	
	if (Player->CurrentAnimationDuration > 0)
	{
		Player->CurrentAnimationDuration -= DeltaTime;
	}
	else if (InputBuffer.Num()>0)
	{
		if(InputBuffer.Contains(InputAction::MeleeAbility) && Player->MeleeComboCount > 0)
		{
			//UE_LOG(LogTemp, Display, TEXT("Executed BufferAction"));
			DoAction(InputBuffer.Last());
			InputBuffer.Empty();
		} else if (Player->PlayerAnim->AnimationFinished == true)
		{
			//UE_LOG(LogTemp, Display, TEXT("Executed BufferAction"));
			DoAction(InputBuffer.Last());
			InputBuffer.Empty();
		}
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
	MoveX = Value;
}

void UInputManager::MoveRight(float Value)
{
	MoveY = Value;
}

void UInputManager::MeleeAbility()
{
	if(!Player->Dead)
	{
		AddToBuffer(InputAction::MeleeAbility);
	}
}

void UInputManager::RangedAbility()
{
	if(!Player->Dead)
	{
		AddToBuffer(InputAction::RangedAbility);
	}
}

void UInputManager::SpecialAbility()
{
	if(!Player->Dead)
	{
		AddToBuffer(InputAction::SpecialAbility);
	}
}

void UInputManager::Dash()
{
	if(!Player->Dead)
	{
		DoAction(InputAction::Dash);
	}
}

void UInputManager::Move()
{
	if (!Player->Dead)
	{
		MoveInput.X = MoveX;
		MoveInput.Y = MoveY;
		if(Player->PlayerAnim->Melee)
		{
			if (UKismetMathLibrary::Acos(FVector::DotProduct(GetOwner()->GetActorForwardVector(), MoveInput)) < 1.5)
			{
				GetOwner()->SetActorRotation(MoveInput.Rotation());
				MoveInput = GetOwner()->GetActorForwardVector();
				MovementComponent->SetDirection(MoveInput, Player->
						MovementSpeedWhileAttacking, false, false);
			}
		
		}else
		{
			MovementComponent->SetDirection(MoveInput, Player->Stats[Movespeed], false, false);
		}
	}
}

void UInputManager::AddToBuffer(InputAction _InputAction)
{
	if(Player->CurrentAnimationDuration <= 0 && InputBuffer.Num() == 0)
	{
		DoAction(_InputAction);
	} else if (Player->CurrentAnimationDuration <= MaxBufferTime)
	{
		InputBuffer.Add(_InputAction);
		
		//UE_LOG(LogTemp, Display, TEXT("Added Action to buffer"));
	}
}

void UInputManager::DoAction(InputAction _InputAction)
{
	switch (_InputAction)
	{
	case InputAction::Dash:
		if (Player->CurrentDashCooldown <= 0)
		{
			LastAction = InputAction::Dash;
			//static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnDashKeyPressed();
			//UE_LOG(LogTemp, Display, TEXT("Used Dash"));
		}
		break;
	case InputAction::MeleeAbility:

		if(Player->MeleeComboCount!=0)
		{
			LastAction = InputAction::MeleeAbility;
			//static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnMeleeKeyPressed();
			//UE_LOG(LogTemp, Display, TEXT("Used Melee"));
		} else
		{
			if(Player->PlayerAnim->AnimationFinished)
			{
				LastAction = InputAction::MeleeAbility;
				//static_cast<APlayerCharacter*>(GetOwner())->AttackManager->OnMeleeKeyPressed();
				//UE_LOG(LogTemp, Display, TEXT("Used Melee"));
			}
		}
		
		break;
	case InputAction::RangedAbility:
	    if(Player->AttackManager->CheckCooldown(Ranged))
	    {
	    	if(Player->PlayerAnim->AnimationFinished)
	    	{
	    		MoveLock = true;
	    		Player->MovementComponent->DirectionSet = false;
	    		Player->MovementComponent->Rotating = false;
	    		Player->RotateToClosestEnemy();
	    		
	    		LastAction = InputAction::RangedAbility;
	    		//Player->AttackManager->OnKeyPressed(Ranged, Player->SkeletalMesh->GetSocketLocation("LeftHandSocket"));
	    		//UE_LOG(LogTemp, Display, TEXT("Used Ranged"));
	    	}
	    }
		break;
	case InputAction::SpecialAbility:
		if(Player->AttackManager->CheckCooldown(Special))
		{
			if(Player->PlayerAnim->AnimationFinished)
			{
				LastAction = InputAction::SpecialAbility;
				//Player->AttackManager->OnKeyPressed(Special, Player->GetActorLocation());
				//UE_LOG(LogTemp, Display, TEXT("Used Special"));
			}
		}
		break;
	default:
		break;
	}
}