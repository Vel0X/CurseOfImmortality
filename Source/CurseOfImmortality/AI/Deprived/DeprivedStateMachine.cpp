// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/AI/Deprived/DeprivedStateMachine.h"

#include "DeprivedPawn.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "CurseOfImmortality/AI/AIBaseClasses/State.h"
#include "States/DeprivedHitPlayer.h"
#include "States/DeprivedIdle.h"
#include "States/DeprivedJumpAttack.h"
#include "States/DeprivedNormalAttack.h"
#include "States/DeprivedRecover.h"
#include "States/DeprivedRunning.h"

UDeprivedStateMachine::UDeprivedStateMachine()
{
}

void UDeprivedStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentState->OnStateUpdate(DeltaTime);

	FVector PlayerLocation(Player->GetActorLocation());
	FVector OwnLocation(SelfRef->GetActorLocation());
	FVector RightVectorSelf(SelfRef->GetActorRightVector());
	FVector LeftVectorSelf(RightVectorSelf.operator-());
	FVector RightVectorPlayer(Player->GetActorRightVector());
	FVector LeftVectorPlayer(RightVectorPlayer.operator-());
	FVector StartPointLeft(LeftVectorSelf * SelfRef->GetCollisionCapsule()->GetUnscaledCapsuleRadius() + OwnLocation);
	FVector EndPointLeft(LeftVectorPlayer * Player->CapsuleComponent->GetUnscaledCapsuleRadius() + PlayerLocation);
	FVector StartPointRight(RightVectorSelf * SelfRef->GetCollisionCapsule()->GetUnscaledCapsuleRadius() + OwnLocation);
	FVector EndPointRight(RightVectorPlayer * Player->CapsuleComponent->GetUnscaledCapsuleRadius() + PlayerLocation);

	DrawDebugLine(GetWorld(), OwnLocation, PlayerLocation, FColor::Red);
	DrawDebugLine(
		GetWorld(), RightVectorSelf * SelfRef->GetCollisionCapsule()->GetUnscaledCapsuleRadius() + OwnLocation,
		RightVectorPlayer * Player->CapsuleComponent->GetUnscaledCapsuleRadius() + PlayerLocation, FColor::Blue);
	DrawDebugLine(
		GetWorld(), LeftVectorSelf * SelfRef->GetCollisionCapsule()->GetUnscaledCapsuleRadius() + OwnLocation,
		LeftVectorPlayer * Player->CapsuleComponent->GetUnscaledCapsuleRadius() + PlayerLocation, FColor::Green);


	SelfRef->CurrentJumpAttackCoolDown -= DeltaTime;
}

void UDeprivedStateMachine::BeginPlay()
{
	Super::BeginPlay();

	//Initialise References
	SelfRef = Cast<ADeprivedPawn>(GetOwner());
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	//Initialise States
	Idle = NewObject<UDeprivedIdle>();
	Running = NewObject<UDeprivedRunning>();
	JumpAttack = NewObject<UDeprivedJumpAttack>();
	HitPlayer = NewObject<UDeprivedHitPlayer>();
	Recover = NewObject<UDeprivedRecover>();
	NormalAttack = NewObject<UDeprivedNormalAttack>();

	//Log States
	Idle->Verbose = true;
	Running->Verbose = true;
	JumpAttack->Verbose = true;
	HitPlayer->Verbose = true;
	Recover->Verbose = true;
	NormalAttack->Verbose = true;

	CurrentState = Idle;
	CurrentState->OnStateEnter(this);
}

void UDeprivedStateMachine::MoveToTarget(FVector Target, float Speed)
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	Target = Target - SelfRef->GetActorLocation();
	Target.Z = 0.f;
	Target.Normalize();

	SelfRef->MovementComponent->SetDirection(Target, Speed);
}

void UDeprivedStateMachine::FocusOnPlayer()
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	if (!Player) { UE_LOG(LogTemp, Error, TEXT("No Player in Deprived StateMachine")); }
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Target = PlayerLocation - SelfRef->GetActorLocation();

	const FRotator LookAtRotation = FRotator(0.f, Target.Rotation().Yaw, 0.f);
	SelfRef->GetCollisionCapsule()->SetWorldRotation(LookAtRotation);
}

void UDeprivedStateMachine::FocusOnPath(FVector PathLocation, float DeltaTime)
{
	if (!SelfRef) { UE_LOG(LogTemp, Error, TEXT("No Self Ref in Deprived StateMachine")); }
	const FVector SelfRefLocation(SelfRef->GetActorLocation());
	FVector Target = PathLocation - SelfRefLocation;

	Target.Z = 0;

	const FRotator LookAtRotation(
		FMath::VInterpNormalRotationTo(SelfRef->GetActorForwardVector(), Target, DeltaTime, 270.f).Rotation());

	SelfRef->GetCollisionCapsule()->SetWorldRotation(LookAtRotation);
}

//Getter and Setter
ADeprivedPawn* UDeprivedStateMachine::GetSelfRef() const
{
	if (!SelfRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Self Ref in Deprived StateMachine"))
	}
	return SelfRef;
}

APlayerCharacter* UDeprivedStateMachine::GetPlayer() const
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player in Deprived StateMachine"))
	}
	return Player;
}
