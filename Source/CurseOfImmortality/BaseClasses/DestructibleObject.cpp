// Fill out your copyright notice in the Description page of Project Settings.


#include "CurseOfImmortality/BaseClasses/DestructibleObject.h"

#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void ADestructibleObject::BeginPlay()
{
	Super::BeginPlay();
	FPersistentWorldManager::Arena->DestructibleObjects.Add(this);
}
