#pragma once
#include "ObjectFactory.h"
#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"

class FPersistentWorldManager
{
public:
	static UAttackManager* AttackManager;
	static APlayerCharacter* PlayerCharacter;
	static AObjectFactory* ObjectFactory;
	static APathfindingGrid* PathfindingGrid;

	static TArray<ABaseCharacter*>& GetEnemies()
	{
		return Enemies;
	}

private:
	static TArray<ABaseCharacter*> Enemies;
};
