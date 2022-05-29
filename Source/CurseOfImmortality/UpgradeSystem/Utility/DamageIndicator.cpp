// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageIndicator.h"

#include "Components/TextRenderComponent.h"


// Sets default values
ADamageIndicator::ADamageIndicator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>("Text");
	TextComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADamageIndicator::BeginPlay()
{
	Super::BeginPlay();
	RemainingLifetime = LifeTime;
}

// Called every frame
void ADamageIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RemainingLifetime -= DeltaTime;
	const float CurrentPercentage = 1 - (RemainingLifetime/LifeTime);
	const FVector OffsetDelta = MoveDirection * DeltaTime * MoveSpeed * 100.0f * SpeedOverTime->GetFloatValue(CurrentPercentage); 
	AddActorWorldOffset(OffsetDelta);
	if(RemainingLifetime <= 0.0f)
	{
		Destroy();
	}
}

void ADamageIndicator::SetText(const FString Text) const
{
	const FText T = T.FromString(Text);
	TextComponent->SetText(T);
}
