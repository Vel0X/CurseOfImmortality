// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

ADeprivedPawn::ADeprivedPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	JumpAttackSphere = CreateDefaultSubobject<USphereComponent>("JumpAttackSphere");
	JumpAttackSphere->SetupAttachment(RootComponent);

	NormalAttackSphereLeft = CreateDefaultSubobject<USphereComponent>("NormalAttackSphereLeft");
	NormalAttackSphereLeft->SetupAttachment(Mesh, "LeftHandSocket");

	NormalAttackSphereRight = CreateDefaultSubobject<USphereComponent>("NormalAttackSphereRight");
	NormalAttackSphereRight->SetupAttachment(Mesh, "RightHandSocket");

	NormalAttackSphereArray.Add(NormalAttackSphereLeft);
	NormalAttackSphereArray.Add(NormalAttackSphereRight);

	StateMachine = CreateDefaultSubobject<UDeprivedStateMachine>("StateMachine");

	CurrentJumpAttackCoolDown = 0.f;
	CurrentJumpAttackChargeTime = JumpAttackChargeTime;
	CurrentRecoverDuration = RecoverDuration;
	CurrentNormalAttackDuration = NormalAttackDuration;
	CurrentJumpAttackDuration = JumpAttackDuration;
}

void ADeprivedPawn::ReceiveDamage(float Damage)
{
	Super::ReceiveDamage(Damage);

	Health -= Damage;
	if (Health <= 0)
	{
		Dead = true;
		StateMachine->DestroyComponent();
		GetCollisionCapsule()->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

void ADeprivedPawn::DealDamage(float Damage, ABaseCharacter* EnemyCharacter)
{
	Super::DealDamage(Damage, EnemyCharacter);
	EnemyCharacter->ReceiveDamage(Damage);
}
