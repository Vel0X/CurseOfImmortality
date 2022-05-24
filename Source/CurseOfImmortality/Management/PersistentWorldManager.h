#pragma once
#include "ObjectFactory.h"
#include "CurseOfImmortality/AI/AIBaseClasses/Pathfinding/PathfindingGrid.h"
#include "CurseOfImmortality/Arena/Arena.h"
#include "CurseOfImmortality/MainCharacter/PlayerCharacter.h"
#include "Rounds/RoundsManager.h"

class FPersistentWorldManager
{
public:
	static UAttackManager* AttackManager;
	static APlayerCharacter* PlayerCharacter;
	static AObjectFactory* ObjectFactory;
	static APathfindingGrid* PathfindingGrid;
	static ARoundsManager* RoundsManager;
	static AArena* Arena;

	static TArray<ABaseCharacter*> GetEnemies()
	{
		return Enemies;
	}

	
	static TArray<ABaseCharacter*> GetFriendly()
	{
		return Friendly;
	}

	static void RegisterCharacter(ABaseCharacter* Character)
	{
		switch(Character->Faction)
		{
		case EFaction::Friendly:
			Friendly.Add(Character);
			break;
		case EFaction::Enemy:
			Enemies.Add(Character);
			break;
		default: ;
		}
	}

	static void DeRegisterCharacter(ABaseCharacter* Character)
	{
		switch(Character->Faction)
		{
		case EFaction::Friendly:
			Friendly.Remove(Character);
			break;
		case EFaction::Enemy:
			Enemies.Remove(Character);
			break;
		default: ;
		}
	}

	static void Clear()
	{
		Enemies.Empty();
		Friendly.Empty();
		AttackManager = nullptr;
		PlayerCharacter = nullptr;
		ObjectFactory = nullptr;
		RoundsManager = nullptr;
		Arena = nullptr;
	}

private:
	static TArray<ABaseCharacter*> Enemies;
	static TArray<ABaseCharacter*> Friendly;
};
