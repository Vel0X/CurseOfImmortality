// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "PlayerCharacterStateMachine.h"
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
	SkeletalMesh->SetupAttachment(CapsuleComponent);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(CapsuleComponent);
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);
	InputManager = CreateDefaultSubobject<UInputManager>(TEXT("InputManager"));
	AttackManager = CreateDefaultSubobject<UAttackManager>(TEXT("AttackManager"));
	StateMachine = CreateDefaultSubobject<UPlayerCharacterStateMachine>(TEXT("StateMachine"));
	
}
 

// Called when the game starts or when spawned
void APlayerCharacter::Setup()
{
	Super::Setup();
	PlayerAnim = Cast<UPlayerAnim>(SkeletalMesh->GetAnimInstance());
	StateMachine->Initialize();
	FPersistentWorldManager::PlayerCharacter = this;
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
	const FVector Start = GetActorLocation();
	const FVector End = GetActorLocation();

	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(this);

	TArray<FHitResult> HitArray;
	float ClosestDistance = SphereTraceRadius;
	FVector ForwardInSphere = GetActorForwardVector() * SphereTraceRadius;
	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Start, End, SphereTraceRadius, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::None,HitArray, true, FLinearColor::Gray, FLinearColor::Blue, 60.0f);
	if (Hit)
	{
		AActor* ClosestActor = this;
		FHitResult ClosestHit;
		for(const FHitResult HitResult : HitArray)
		{
			if(Cast<ABaseCharacter>(HitResult.GetActor()) != nullptr)
			{
				float DotProduct = FVector::DotProduct(GetActorForwardVector(),HitResult.ImpactNormal);
				float Magnitude = GetActorForwardVector().Size() * HitResult.ImpactNormal.Size();
				float Angle = FMath::RadiansToDegrees(UKismetMathLibrary::Acos(DotProduct/Magnitude));
				
				if(Angle > 135)
				{
					if((UKismetMathLibrary::Sin(Angle) * (Start - HitResult.GetActor()->GetActorLocation()).Length()) < ClosestDistance)
					{
						float Distance = (Start - HitResult.GetActor()->GetActorLocation()).Length();
						ClosestDistance = UKismetMathLibrary::Sin(Angle) * (Start - HitResult.GetActor()->GetActorLocation()).Length();
						ClosestActor = HitResult.GetActor();
						ClosestHit = HitResult;
					}
				}
				/*if ((Start - HitResult.GetActor()->GetActorLocation()).Length() <= ClosestDistance)
				{
					ClosestActor = HitResult.GetActor();
					ClosestHit = HitResult;
				}*/
			}
		}
		if (ClosestActor != this)
		{
			SetActorRotation(UKismetMathLibrary::MakeRotFromXZ(ClosestActor->GetActorLocation()-GetActorLocation(), FVector::UpVector));
		}
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
