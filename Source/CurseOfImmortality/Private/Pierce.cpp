// Fill out your copyright notice in the Description page of Project Settings.


#include "Pierce.h"

void UPierce::OnEnemyHit()
{
	Super::OnEnemyHit();
	
	ABaseAbility* Owner = static_cast<ABaseAbility*>(GetOwner());
	if(PiercesLeft > 0)
	{
		Owner->DestroyOnEnemyHit = false;
		PiercesLeft--;
	}
	else
	{
		Owner->DestroyOnEnemyHit = true;
	}
	
}
