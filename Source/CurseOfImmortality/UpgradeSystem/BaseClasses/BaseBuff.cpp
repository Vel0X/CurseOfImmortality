// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuff.h"

#include "CurseOfImmortality/UpgradeSystem/GameDummy/Char.h"


// Sets default values for this component's properties
UBaseBuff::UBaseBuff()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}

void UBaseBuff::OnTakeDamage(int AbilityHandle)
{
}

void UBaseBuff::OnBuffBegin()
{
}

void UBaseBuff::OnBuffTick(float DeltaTime)
{
	if(!CustomBuffEnd)
	{
		if(RemainingDuration <= 0.0f)
		{
			Owner->RemoveBuff(this);
		}
		RemainingDuration -= DeltaTime;
	}

}

void UBaseBuff::OnBuffEnd()
{
}

void UBaseBuff::IntitializeBuff(int Level, AChar* _Owner)
{
	Owner = _Owner;
	RemainingDuration = BuffDuration;
}
