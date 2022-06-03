#include "PersistentWorldManager.h"

ASoundManager* FPersistentWorldManager::SoundManager = nullptr;
UAttackManager* FPersistentWorldManager::AttackManager = nullptr;
APlayerCharacter* FPersistentWorldManager::PlayerCharacter = nullptr;
AObjectFactory* FPersistentWorldManager::ObjectFactory = nullptr;
APathfindingGrid* FPersistentWorldManager::PathfindingGrid = nullptr;
ARoundsManager* FPersistentWorldManager::RoundsManager = nullptr;
AArena* FPersistentWorldManager::Arena = nullptr;
TArray<ABaseCharacter*> FPersistentWorldManager::Enemies = TArray<ABaseCharacter*>();
TArray<ABaseCharacter*> FPersistentWorldManager::Friendly = TArray<ABaseCharacter*>();
TMap<FString, bool> FPersistentWorldManager::Logs = {
	{"round", false},
	{"playerstatemachine", false},
	{"mawstatemachine", false},
	{"damagecomponent", false},
	{"buff", false}
};

TMap<FString, bool> FPersistentWorldManager::ControlFlags = {
	{"automaticroundincrement", false},
	{"sfx", true},
	{"music", true}
};