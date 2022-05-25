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
		switch (Character->Faction)
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
		switch (Character->Faction)
		{
		case EFaction::Friendly:
			Friendly.Remove(Character);
			break;
		case EFaction::Enemy:
			Enemies.Remove(Character);

			if (RoundsManager != nullptr)
			{
				ABaseEnemyPawn* E = Cast<ABaseEnemyPawn>(Character);
				if (E != nullptr)
				{
					RoundsManager->OnEnemyDied(E);
				}
			}

			break;
		default: ;
		}
	}

	static void SetControlFlag(const FString Key, const bool Value)
	{
		const FString LowerKey = Key.ToLower();
		if (ControlFlags.Contains(LowerKey))
		{
			ControlFlags[LowerKey] = Value;
		}
	}

	static bool GetControlFlag(const EControlFlag Flag)
	{
		switch (Flag)
		{
		case AutomaticRoundIncrement:
			return ReturnIfControlflagsContains("automaticroundincrement");
		}
		return false;
	}

	static void SetLogLevel(const FString Key, const bool Value)
	{
		const FString LowerKey = Key.ToLower();
		if (Logs.Contains(LowerKey))
		{
			Logs[LowerKey] = Value;
		}
	}

	static bool GetLogLevel(const ELog Log)
	{
		switch (Log)
		{
		case Round:
			return ReturnIfContains("round");

		case PlayerStateMachine:
			return ReturnIfContains("playerstatemachine");

		case DamageComponent:
			return ReturnIfContains("damagecomponent");

		case MawStateMachine:
			return ReturnIfContains("mawstatemachine");
		}
		return false;
	}

	static bool ReturnIfContains(const FString Key)
	{
		return Logs.Contains(Key) ? Logs[Key] : false;
	}

	static bool ReturnIfControlflagsContains(const FString Key)
	{
		return ControlFlags.Contains(Key) ? ControlFlags[Key] : false;
	}

	/**
	 * @brief Invalidate all of the pointers when the game ends
	 */
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

	static TMap<FString, bool> Logs;
	static TMap<FString, bool> ControlFlags;
};
