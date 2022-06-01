// Fill out your copyright notice in the Description page of Project Settings.


#include "LingeringDamageObject.h"

bool ULingeringDamageObject::DealDamage(ABaseCharacter* Character)
{
	if(TimeUntilNextHit <= 0.0f)
	{
		return Super::DealDamage(Character);
	}

	return false;
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
