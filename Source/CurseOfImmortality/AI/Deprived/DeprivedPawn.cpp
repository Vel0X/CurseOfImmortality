// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"
#include "CurseOfImmortality/BaseClasses/Damage/DamageComponent.h"

ADeprivedPawn::ADeprivedPawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	JumpAttackSphere = CreateDefaultSubobject<USphereComponent>("JumpAttackSphere");
	JumpAttackSphere->SetupAttachment(RootComponent);


	AttackSphereLeft = CreateDefaultSubobject<USphereComponent>("AttackSphereLeft");
	AttackSphereLeft->SetupAttachment(Mesh, "LeftHandSocket");
	
	AttackSphereRight = CreateDefaultSubobject<USphereComponent>("AttackSphereRight");
	AttackSphereRight->SetupAttachment(Mesh, "RightHandSocket");

	StateMachine = CreateDefaultSubobject<UDeprivedStateMachine>("StateMachine");
	
	CurrentRecoverDuration = RecoverDuration;
}

void ADeprivedPawn::OnDeath()
{
	Super::OnDeath();
	StateMachine->DestroyComponent();
	//CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void ADeprivedPawn::ToggleJumpAttackDamage()
{
	JumpAttackSphere->SetGenerateOverlapEvents(!JumpAttackSphere->GetGenerateOverlapEvents());
	DamageComponent->ResetAllHitCharacters();
}

void ADeprivedPawn::ToggleLeftHand()
{
	AttackSphereLeft->SetGenerateOverlapEvents(!AttackSphereLeft->GetGenerateOverlapEvents());
	DamageComponent->ResetAllHitCharacters();
}

void ADeprivedPawn::ToggleRightHand()
{
	AttackSphereRight->SetGenerateOverlapEvents(!AttackSphereRight->GetGenerateOverlapEvents());
	DamageComponent->ResetAllHitCharacters();
}
