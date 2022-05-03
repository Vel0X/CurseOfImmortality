// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomAOEAbilty.h"

#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
URandomAOEAbilty::URandomAOEAbilty()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URandomAOEAbilty::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void URandomAOEAbilty::StartAbility()
{
	FVector PlayerLocation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
	PlayerLocation.Z = 0;

	const FVector2d RandomPoint = FMath::RandPointInCircle(RangeAroundPlayer);
	FVector RandomPoint3D(RandomPoint, 0);

	FVector DamageFieldLocation = PlayerLocation + RandomPoint3D;

	DrawDebugSphere(GetWorld(), DamageFieldLocation, DamageField, 20, FColor::Red, true, DamageDuration);
}


// Called every frame
void URandomAOEAbilty::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
