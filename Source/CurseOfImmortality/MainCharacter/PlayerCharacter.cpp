// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "PlayerCharacterStateMachine.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"
#include "CurseOfImmortality/AI/Deprived/States/DeprivedFrenziedAttack.h"
#include "CurseOfImmortality/MainCharacter/PlayerAnim.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/AttackManager.h"
#include "CurseOfImmortality/BaseClasses/BaseCharacter.h"
#include "CurseOfImmortality/MainCharacter/InputManager.h"
#include "Kismet/KismetSystemLibrary.h"
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

	SkeletalMesh->SetupAttachment(RootComponent);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);
	InputManager = CreateDefaultSubobject<UInputManager>(TEXT("InputManager"));
	AttackManager = CreateDefaultSubobject<UAttackManager>(TEXT("AttackManager"));
	StateMachine = CreateDefaultSubobject<UPlayerCharacterStateMachine>(TEXT("StateMachine"));
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	Weapon->SetupAttachment(SkeletalMesh, "RightHandSocket");

	SoundSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SoundSphere"));
	SoundSphere->SetupAttachment(RootComponent);
}

APlayerCharacter::~APlayerCharacter()
{
}


// Called when the game starts or when spawned
void APlayerCharacter::Setup()
{
	Super::Setup();
	PlayerAnim = Cast<UPlayerAnim>(SkeletalMesh->GetAnimInstance());
	StateMachine->Initialize();
	FPersistentWorldManager::PlayerCharacter = this;

	WeaponMaterialInst = Weapon->CreateAndSetMaterialInstanceDynamic(0);

	SetupInputComponent();
	//DamageComponent->ConvertInterface();
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::OnDeath()
{
	Super::OnDeath();
}

void APlayerCharacter::RotateToClosestEnemy()
{
	TArray<ABaseCharacter*> AllEnemies = FPersistentWorldManager::GetEnemies();
	float ClosestDistance = 1200.0f;
	float MaxDistance = 1200.0f;
	ABaseCharacter* ClosestActor = this;
	for (ABaseCharacter* Enemy : AllEnemies)
	{
		float DotProduct = FVector::DotProduct(GetActorForwardVector(), (Enemy->GetActorLocation() - GetActorLocation()).GetSafeNormal());
		float Angle = FMath::RadiansToDegrees(UKismetMathLibrary::Acos(DotProduct));
		if (Angle < 125 && Angle > -125 && MaxDistance > (GetActorLocation() - Enemy->GetActorLocation()).Length())
		{
			if (Angle < ClosestDistance)
			{
				FHitResult HResult;
				FCollisionQueryParams Params;
				Params.AddIgnoredActor(GetOwner());
				if (!GetWorld()->LineTraceSingleByChannel(HResult, CenterAttachmentPoint->GetComponentLocation(),
														  Enemy->CenterAttachmentPoint->GetComponentLocation(), ECollisionChannel::ECC_Visibility,
														  Params, FCollisionResponseParams()))
				{
					ClosestDistance = Angle;
					ClosestActor = Enemy;
				}
			}
			/*if ((UKismetMathLibrary::Sin(Angle) * (GetActorLocation() - Enemy->GetActorLocation()).Length()) <
				ClosestDistance)
			{
				FHitResult HResult;
				FCollisionQueryParams Params;
				Params.AddIgnoredActor(GetOwner());
				if (!GetWorld()->LineTraceSingleByChannel(HResult, CenterAttachmentPoint->GetComponentLocation(),
				                                          Enemy->CenterAttachmentPoint->GetComponentLocation(), ECollisionChannel::ECC_Visibility,
				                                          Params, FCollisionResponseParams()))
				{
					ClosestDistance = UKismetMathLibrary::Sin(Angle) * (GetActorLocation() - Enemy->GetActorLocation()).
						Length();
					ClosestActor = Enemy;
				}
			}*/
		}
	}
	if (ClosestActor != this)
	{
		SetActorRotation(
			UKismetMathLibrary::MakeRotFromXZ(ClosestActor->GetActorLocation() - GetActorLocation(),
			                                  FVector::UpVector));
	}
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

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//Weapon->SetMaterial(0, WeaponMaterial);
	Super::EndPlay(EndPlayReason);
}

int APlayerCharacter::GetDeprivedCount()
{
	int Count = 0;

	TArray<AActor*> OverlappingActorArray;

	SoundSphere->GetOverlappingActors(OverlappingActorArray);

	// UE_LOG(LogTemp, Warning, TEXT("%s"), OverlappingActorArray.Num())

	for (AActor* Actor : OverlappingActorArray)
	{
		if (Cast<ADeprivedPawn>(Actor))
		{
			Count++;
		}
	}
	return OverlappingActorArray.Num();
}
