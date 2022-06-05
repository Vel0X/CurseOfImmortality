// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"

#include "MawOfSothrosStateMachine.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageComponent.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/MawSlam.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/AbilitySpecification.h"

AMawOfSothrosPawn::AMawOfSothrosPawn()
{
	StateMachine = CreateDefaultSubobject<UMawOfSothrosStateMachine>("State Machine");

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	PuddleUpperSpawnLocation = CreateDefaultSubobject<USceneComponent>("Upper Spawn Location");
	PuddleUpperSpawnLocation->SetupAttachment(RootComponent);

	PuddleLowerSpawnLocation = CreateDefaultSubobject<USceneComponent>("Lower Spawn Location");
	PuddleLowerSpawnLocation->SetupAttachment(RootComponent);

	VomitUpperJaw = CreateDefaultSubobject<UNiagaraComponent>("Vomit Upper Jaw");
	VomitUpperJaw->SetupAttachment(Mesh, "Upper Jaw");

	VomitLowerJaw = CreateDefaultSubobject<UNiagaraComponent>("Vomit Lower Jaw");
	VomitLowerJaw->SetupAttachment(Mesh, "Lower Jaw");

	MawSmoke = CreateDefaultSubobject<UNiagaraComponent>("Maw Smoke");
	MawSmoke->SetupAttachment(Mesh);

	//Collision
	UpperBodyCollision = CreateDefaultSubobject<UCapsuleComponent>("Upper Body Collision");
	UpperBodyCollision->SetupAttachment(Mesh, "UpperBodyCollisionSocket");
	UpperLeftArmCollision = CreateDefaultSubobject<UCapsuleComponent>("Upper Left Arm Collision");
	UpperLeftArmCollision->SetupAttachment(Mesh, "UpperLeftArmCollisionSocket");
	LowerLeftArmCollision = CreateDefaultSubobject<UCapsuleComponent>("Lower Left Arm Collision");
	LowerLeftArmCollision->SetupAttachment(Mesh, "LowerLeftArmCollisionSocket");
	UpperRightArmCollision = CreateDefaultSubobject<UCapsuleComponent>("Upper Right Arm Collision");
	UpperRightArmCollision->SetupAttachment(Mesh, "UpperRightArmCollisionSocket");
	LowerRightArmCollision = CreateDefaultSubobject<UCapsuleComponent>("Lower Right Arm Collision");
	LowerRightArmCollision->SetupAttachment(Mesh, "LowerRightArmCollisionSocket");
	HeadCollision = CreateDefaultSubobject<USphereComponent>("Head Collision");
	HeadCollision->SetupAttachment(Mesh, "HeadCollisionSocket");

	//Damage
	LeftArmDamageCapsule = CreateDefaultSubobject<UCapsuleComponent>("Left Arm Damage Capsule");
	LeftArmDamageCapsule->SetupAttachment(Mesh, "LowerLeftArmCollisionSocket");
	RightArmDamageCapsule = CreateDefaultSubobject<UCapsuleComponent>("Right Arm Damage Capsule");
	RightArmDamageCapsule->SetupAttachment(Mesh, "LowerRightArmCollisionSocket");
	HeadDamageSphere = CreateDefaultSubobject<USphereComponent>("HeadDamageSphere");
	HeadDamageSphere->SetupAttachment(Mesh, "HeadCollisionSocket");
	TailDamageSphere = CreateDefaultSubobject<USphereComponent>("TailDamageSphere");
	TailDamageSphere->SetupAttachment(Mesh, "TailDamageSphere");
	SmokeDamageSphere = CreateDefaultSubobject<USphereComponent>("SmokeDamageSphere");
	SmokeDamageSphere->SetupAttachment(Mesh);
}

void AMawOfSothrosPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const FVector PlayerPosition = FPersistentWorldManager::PlayerCharacter->GetAttachmentLocation(CenterPoint)->GetComponentLocation(); //Player Location
	FVector BoneLocation = Mesh->GetBoneLocation("Bone_006"); //Neck Bone Location
	FVector Dir = PlayerPosition - BoneLocation;// + FVector(0,0,500.0f);
	Dir.Normalize();
	const FVector Cross = FVector::UpVector.Cross(Dir);

	const float ACos = FMath::Acos(GetActorForwardVector().Dot(Dir));
	if( ACos < 1.0f)
		TargetHeadRotation = Cross.Rotation();

	FVector PlayerLoc = FPersistentWorldManager::PlayerCharacter->GetActorLocation();
	PlayerLoc.Z = 0.0f;
	const float HeightDiff = BoneLocation.Z + 400.0f;
	BoneLocation.Z = 0.0f;
	const float Dist = FVector::Dist(PlayerLoc, BoneLocation);
	const float Hypotenuse = FMath::Sqrt(Dist * Dist + HeightDiff * HeightDiff);

	const float Beta = FMath::Asin(HeightDiff / Hypotenuse);
	
	const float RollAngle = -(90 - (90 - FMath::RadiansToDegrees(Beta)));
	//UE_LOG(LogTemp, Error, TEXT("HeightDiff %f"), HeightDiff);
	//UE_LOG(LogTemp, Error, TEXT("Dist %f"), Dist);
	//UE_LOG(LogTemp, Error, TEXT("Beta %f"), FMath::RadiansToDegrees(Beta));

	//const float RollRadians = FMath::Acos(GetActorForwardVector().Dot())
	TargetHeadRotation.Roll = RollAngle;
	//else
	//	TargetHeadRotation = FVector::UpVector.Cross(GetActorForwardVector()).Rotation();
	HeadRotation = FMath::RInterpTo(HeadRotation, TargetHeadRotation, DeltaSeconds, 7.0f);

	
}

void AMawOfSothrosPawn::ActivateVomit()
{
	VomitLowerJaw->Activate();
	VomitUpperJaw->Activate();

	SpawnPuddle = true;
}

void AMawOfSothrosPawn::DeactivateVomit()
{
	VomitLowerJaw->Deactivate();
	VomitUpperJaw->Deactivate();

	SpawnPuddle = false;
}

void AMawOfSothrosPawn::ToggleArmDamage()
{
	LeftArmDamageCapsule->SetGenerateOverlapEvents(!LeftArmDamageCapsule->GetGenerateOverlapEvents());
	RightArmDamageCapsule->SetGenerateOverlapEvents(!RightArmDamageCapsule->GetGenerateOverlapEvents());

	DamageComponent->ResetAllHitCharacters();
}

void AMawOfSothrosPawn::ToggleHeadDamage()
{
	HeadDamageSphere->SetGenerateOverlapEvents(!HeadDamageSphere->GetGenerateOverlapEvents());

	DamageComponent->ResetAllHitCharacters();
}

void AMawOfSothrosPawn::SpawnAbility(FName SocketName)
{
	const FVector SpawnLocation = Mesh->GetSocketLocation(SocketName);
	AMawSlam* AbilityInstance = Cast<AMawSlam>(
		GetWorld()->SpawnActor(MawSlamSpecification->Class,
		                       &SpawnLocation,
		                       &FRotator::ZeroRotator));

	AbilityInstance->InitializeAbility(this, 1);

	DrawDebugSphere(GetWorld(), AbilityInstance->Collider->GetComponentLocation(), 500, 20, FColor::Green, true);

	if (AbilityInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Abiltiy could not be spawned in MawGroundSlam!"));
		return;
	}
}
