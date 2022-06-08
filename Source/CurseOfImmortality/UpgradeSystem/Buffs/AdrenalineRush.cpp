// Fill out your copyright notice in the Description page of Project Settings.


#include "AdrenalineRush.h"

#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"

bool UAdrenalineRush::AddBuffStack()
{
	PC = Cast<APlayerCharacter>(Owner);
	const bool AddedStack =  Super::AddBuffStack();

	if(PC)
	{
		const float Val = CurrentStacks / static_cast<float>(MaxStacks);
		CurrentGlow = Val * Val;
		PC->WeaponMaterialInst->SetScalarParameterValue("Glow", CurrentGlow);
	}
	
	return AddedStack;
}

void UAdrenalineRush::OnBuffBegin()
{
	Super::OnBuffBegin();
	PC = Cast<APlayerCharacter>(Owner);
}

void UAdrenalineRush::OnBuffTick(float DeltaTime)
{

	Super::OnBuffTick(DeltaTime);

	if(PC)
	{
		if(CurrentGlow > 0.0f)
			CurrentGlow -= DeltaTime * (1.0f/BuffDuration) * CurrentStacks / static_cast<float>(MaxStacks);

		PC->WeaponMaterialInst->SetScalarParameterValue("Glow", CurrentGlow);
	}
}

void UAdrenalineRush::OnBuffEnd()
{
	Super::OnBuffEnd();
	if(PC)
	{
		PC->WeaponMaterialInst->SetScalarParameterValue("Glow", 0.0f);
	}
}

