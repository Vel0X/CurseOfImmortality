// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/MainCharacter/PlayerAnim.h"

void UPlayerAnim::SyncAnimAttackSpeed(float PlayerAttackSpeed)
{
	this->AttackSpeed = PlayerAttackSpeed;
	MeleeDuration1 = BaseMeleeDuration1 / PlayerAttackSpeed;
	MeleeDuration2 = BaseMeleeDuration2 / PlayerAttackSpeed;
	MeleeDuration3 = BaseMeleeDuration3 / PlayerAttackSpeed;
	MeleeDuration = BaseMeleeDuration / PlayerAttackSpeed;
	RangedDuration1 = BaseRangedDuration1 / PlayerAttackSpeed;
	SpecialDuration1 = BaseSpecialDuration1 / PlayerAttackSpeed;
}
