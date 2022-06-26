#include "PersistentWorldManager.h"

ASoundManager* FPersistentWorldManager::SoundManager = nullptr;
ACustomGameMode* FPersistentWorldManager::GameMode = nullptr;
UAttackManager* FPersistentWorldManager::AttackManager = nullptr;
APlayerCharacter* FPersistentWorldManager::PlayerCharacter = nullptr;
AObjectFactory* FPersistentWorldManager::ObjectFactory = nullptr;
APathfindingGrid* FPersistentWorldManager::PathfindingGrid = nullptr;
ARoundsManager* FPersistentWorldManager::RoundsManager = nullptr;
AArena* FPersistentWorldManager::Arena = nullptr;
UTrapManagerCopmonent* FPersistentWorldManager::TrapManager = nullptr;
TArray<ABaseCharacter*> FPersistentWorldManager::Enemies = TArray<ABaseCharacter*>();
TArray<ABaseCharacter*> FPersistentWorldManager::Friendly = TArray<ABaseCharacter*>();
TMap<FString, bool> FPersistentWorldManager::Logs = {
	{"round", false},
	{"playerstatemachine", false},
	{"mawstatemachine", false},
	{"damagecomponent", false},
	{"deprivedstatemachine", false},
	{"stormcallerstatemachine", false},
	{"molochstatemachine", false},
	{"inustatemachine", false},
	{"buff", false}
};

TMap<FString, bool> FPersistentWorldManager::ControlFlags = {
	{"automaticroundincrement", false},
	{"sfx", true},
	{"music", true}
};
