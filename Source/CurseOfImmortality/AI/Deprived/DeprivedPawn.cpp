// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedPawn.h"

#include "NiagaraComponent.h"
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
}
