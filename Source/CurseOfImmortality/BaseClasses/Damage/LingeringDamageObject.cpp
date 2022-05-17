// Fill out your copyright notice in the Description page of Project Settings.


#include "LingeringDamageObject.h"

void ULingeringDamageObject::DealDamage(ABaseCharacter* Character)
{
	if(TimeUntilNextHit <= 0.0f)
	{
		Super::DealDamage(Character);
	}
}

void ULingeringDamageObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(TimeUntilNextHit > 0.0f)
	{
		TimeUntilNextHit -= DeltaTime;
	}
	else
	{
		TimeUntilNextHit = HitTimer;
		HitCharacters.Empty();
	}
}
