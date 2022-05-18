#pragma once
#include "ObjectFactory.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"

class FPersistentWorldManager
{
public:
	static UAttackManager* AttackManager;
	static APlayerCharacter* PlayerCharacter;
	static AObjectFactory* ObjectFactory;

	static TArray<ABaseCharacter*>& GetEnemies()
	{
		return Enemies;
	}

private:
	static TArray<ABaseCharacter*> Enemies;
};
