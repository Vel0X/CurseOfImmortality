// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/MawOfSothros/States/MawOfSothrosLaser.h"

#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosPawn.h"
#include "CurseOfImmortality/AI/MawOfSothros/MawOfSothrosStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"
#include "CurseOfImmortality/UpgradeSystem/BaseAbilities/LavaCrack.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/DataAssets/AbilitySpecification.h"

void UMawOfSothrosLaser::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UMawOfSothrosStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Laser = true;
	SelfRef->AnimationEnd = false;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Laser State Entered"));
	}
}

void UMawOfSothrosLaser::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->CurrentAttackCooldown = SelfRef->AttackCooldown;

	SelfRef->Laser = false;

	if (FPersistentWorldManager::GetLogLevel(MawStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Laser State Exit"));
	}
}

void UMawOfSothrosLaser::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (!SelfRef->AnimationEnd)
	{
		Controller->FocusOnPlayer(DeltaTime, 60.f);
		FireLaser(DeltaTime);
	}
	else
	{
		Controller->Transition(Controller->Idle, Controller);
	}
}

void UMawOfSothrosLaser::FireLaser(float DeltaTime)
{
	const FVector PlayerPosition = FPersistentWorldManager::PlayerCharacter->GetAttachmentLocation(CenterPoint)->
	                                                                         GetComponentLocation(); //Player Location
	FVector BoneLocation = SelfRef->Mesh->GetBoneLocation("Bone_006"); //Neck Bone Location
	FVector Dir = PlayerPosition - BoneLocation; // + FVector(0,0,500.0f);
	Dir.Normalize();
	const FVector Cross = FVector::UpVector.Cross(Dir);

	const float ACos = FMath::Acos(SelfRef->GetActorForwardVector().Dot(Dir));
	if (ACos < 1.0f)
		TargetHeadRotation = Cross.Rotation();

	FVector PlayerLoc = FPersistentWorldManager::PlayerCharacter->GetActorLocation();
	PlayerLoc.Z = 0.0f;
	const float HeightDiff = BoneLocation.Z;
	BoneLocation.Z = 0.0f;
	const float Dist = FVector::Dist(PlayerLoc, BoneLocation);
	const float Hypotenuse = FMath::Sqrt(Dist * Dist + HeightDiff * HeightDiff);

	const float Beta = FMath::Asin(HeightDiff / Hypotenuse);

	const float RollAngle = -(90 - (90 - FMath::RadiansToDegrees(Beta)));
	TargetHeadRotation.Roll = RollAngle;
	SelfRef->HeadRotation = FMath::RInterpTo(SelfRef->HeadRotation, TargetHeadRotation, DeltaTime, 7.0f);

	if (SelfRef->LaserOn)
	{
		if (SpawnFrequency <= 0)
		{
			SpawnFrequency = 0.01f;

			FHitResult Hit;

			FVector StartPoint = SelfRef->Mesh->GetSocketLocation("LaserSocket");
			FRotator SocketRotation = SelfRef->Mesh->GetSocketRotation("LaserSocket");
			FVector EndPoint = SocketRotation.Vector() * 10000 + StartPoint;

			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(Player);
			CollisionParams.AddIgnoredActor(SelfRef);

			Controller->GetWorld()->LineTraceSingleByChannel(Hit, StartPoint,
			                                                 EndPoint,
			                                                 ECC_WorldStatic, CollisionParams);
			if (Hit.bBlockingHit)
			{
				FVector SpawnLocation(Hit.Location);
				ALavaCrack* AbilityInstance = Cast<ALavaCrack>(SelfRef->GetWorld()->SpawnActor(
					SelfRef->LavaCrackSpecification->Class,
					&SpawnLocation, &FRotator::ZeroRotator));
				if (!AbilityInstance) { return; }
				AbilityInstance->InitializeAbility(SelfRef, 1);
			}
		}
		SpawnFrequency -= DeltaTime;
	}
}
