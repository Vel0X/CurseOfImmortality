#include "PersistentWorldManager.h"

UAttackManager* FPersistentWorldManager::AttackManager = nullptr;
APlayerCharacter* FPersistentWorldManager::PlayerCharacter = nullptr;
AObjectFactory* FPersistentWorldManager::ObjectFactory = nullptr;
APathfindingGrid* FPersistentWorldManager::PathfindingGrid = nullptr;
TArray<ABaseCharacter*> FPersistentWorldManager::Enemies = TArray<ABaseCharacter*>();
TArray<ABaseCharacter*> FPersistentWorldManager::Friendly = TArray<ABaseCharacter*>();
