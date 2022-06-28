// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingGrid.h"

#include <CurseOfImmortality/Management/PersistentWorldManager.h>


APathfindingGrid::APathfindingGrid(): TBaseGrid<FPfNode>(86, 65) //86 65
{
	PrimaryActorTick.bCanEverTick = true;

	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			SetValue(x, y, FPfNode(x, y));
		}
	}
}

void APathfindingGrid::Print()
{
	TBaseGrid<FPfNode>::Print();
	const auto node = GetValue(2, 2);
	UE_LOG(LogTemp, Warning, TEXT("VALUE %d"), node.X);
}

bool APathfindingGrid::ShouldTickIfViewportsOnly() const
{
	return true;
}

void APathfindingGrid::Tick(float DeltaSeconds)
{
	if (ShowNavGrid)
	{
		for (int x = 0; x < Width + 1; ++x)
		{
			auto VS = GetActorLocation() + FVector(x * CellSize, 0, 0);
			auto VE = GetActorLocation() + FVector(x * CellSize, Height * CellSize, 0);

			DrawDebugLine(GetWorld(), VS, VE, FColor::Black, false, -1, 0, 5);
		}

		for (int y = 0; y < Height + 1; ++y)
		{
			auto VS = GetActorLocation() + FVector(0, y * CellSize, 0);
			auto VE = GetActorLocation() + FVector(Width * CellSize, y * CellSize, 0);

			DrawDebugLine(GetWorld(), VS, VE, FColor::Black, false, -1, 0, 5);
		}

		for (int x = 0; x < Width; ++x)
		{
			for (int y = 0; y < Height; ++y)
			{
				FVector WorldPosition;
				GetWorldPositionFromCoordinates(x, y, WorldPosition);
				FColor Color;
				if (GetValue(x, y).IsWalkable)
				{
					if (GetValue(x, y).StaticHeat >= 25 || GetValue(x, y).DynamicHeat >= 25)
					{
						Color = FColor(255, 128, 0, 80);
					}
					else if (GetValue(x, y).StaticHeat >= 12 || GetValue(x, y).DynamicHeat >= 12)
					{
						Color = FColor(255, 255, 0, 80);
					}
					else if (GetValue(x, y).StaticHeat >= 6 || GetValue(x, y).DynamicHeat >= 6)
					{
						Color = FColor(128, 255, 0, 80);
					}
					else if (GetValue(x, y).StaticHeat >= 3 || GetValue(x, y).DynamicHeat >= 3)
					{
						Color = FColor(0, 255, 0, 80);
					}
					else
					{
						Color = FColor(0, 255, 128, 80);
					}
				}
				else
				{
					Color = FColor(255, 0, 50, 80);
				}
				DrawDebugSolidBox(GetWorld(), WorldPosition, FVector(CellSize * 0.5f, CellSize * 0.5f, 0.1f), Color,
				                  false);
			}
		}
	}
}

void APathfindingGrid::BeginPlay()
{
	Super::BeginPlay();

	FPersistentWorldManager::PathfindingGrid = this;
}

void APathfindingGrid::PrintGrid()
{
	for (int y = 0; y < Height; ++y)
	{
		FString s = "|";

		for (int x = 0; x < Width; ++x)
		{
			const char C = GetValue(x, y).IsWalkable ? '0' : 'X';
			s += C;
			s += '|';
		}
	}
}

static constexpr int GMaximumIterations = 100000;

bool APathfindingGrid::GetPath(int StartX, int StartY, int EndX, int EndY, TArray<FPfNode*>& Path, bool Verbose)
{
	TArray<FPfNode*> OpenList, ClosedList;

	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			GetValue(x, y).Reset();
		}
	}


	int CurrentIterations = 0;

	FPfNode* StartNode = &GetValue(StartX, StartY);
	const FPfNode* EndNode = &GetValue(EndX, EndY);
	if (EndNode && !EndNode->IsWalkable)
	{
		TArray<FPfNode*> Neighbours = GetNeighbors(EndNode->X, EndNode->Y);
		for (FPfNode* Node : Neighbours)
		{
			if (Node->IsWalkable)
			{
				EndNode = Node;
				break;
			}
		}
	}
	StartNode->G = 0;
	StartNode->H = CalculateDistance(StartX, StartY, EndX, EndY);
	StartNode->S = StartNode->H;
	OpenList.Add(StartNode);

	while (OpenList.Num() > 0 && CurrentIterations < GMaximumIterations)
	{
		CurrentIterations++;
		FPfNode* Current = GetLowestCostNode(OpenList);


		if (Current == EndNode)
		{
			CalculatePath(Current, Path, Verbose);
			return true;
		}

		OpenList.Remove(Current);
		ClosedList.Add(Current);

		TArray<FPfNode*> Neighbors = GetNeighbors(Current->X, Current->Y);

		for (int i = 0; i < Neighbors.Num(); ++i)
		{
			FPfNode* Neighbor = Neighbors[i];
			if (ClosedList.Contains(Neighbor))
				continue;

			if (!Neighbor->IsWalkable)
			{
				ClosedList.Add(Neighbor);
				continue;
			}

			const int TempGCost = Current->G + CalculateDistance(Current->X, Current->Y, Neighbor->X, Neighbor->Y) +
				Neighbor->StaticHeat + Neighbor->DynamicHeat;

			if (TempGCost < Neighbor->G)
			{
				Neighbor->G = TempGCost;
				Neighbor->H = CalculateDistance(Neighbor->X, Neighbor->Y, EndNode->X, EndNode->Y);
				Neighbor->S = Neighbor->G + Neighbor->H;
				Neighbor->CameFrom = Current;

				if (!OpenList.Contains(Neighbor))
					OpenList.Add(Neighbor);
			}
		}
	}

	//no path found
	return false;
}

bool APathfindingGrid::GetPathWorldSpace(FVector Start, FVector End, TArray<FVector>& WorldSpacePath, bool Verbose)
{
	int SX = 0, SY = 0, EX = 0, EY = 0;
	if (!GetCoordinatesFromWorldPosition(Start, SX, SY))
	{
		UE_LOG(LogTemp, Error, TEXT("Start Position was out of Bounds!"));
		return false;
	}
	if (!GetCoordinatesFromWorldPosition(End, EX, EY))
	{
		UE_LOG(LogTemp, Error, TEXT("EndPosition was out of Bounds!"));
		return false;
	}

	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("SX %i"), SX);
		UE_LOG(LogTemp, Warning, TEXT("SY %i"), SY);
		UE_LOG(LogTemp, Warning, TEXT("EX %i"), EX);
		UE_LOG(LogTemp, Warning, TEXT("EY %i"), EY);
	}

	TArray<FPfNode*> Path;
	if (GetPath(SX, SY, EX, EY, Path, false))
	{
		WorldSpacePath = ConvertPathToWorldSpace(Path, Verbose);
		return true;
	}
	UE_LOG(LogTemp, Warning, TEXT("No Path found"));

	return false;
}

FPfNode* APathfindingGrid::GetRandomNodeInNavMesh()
{
	const int RandomX = FMath::RandRange(0, Width);
	const int RandomY = FMath::RandRange(0, Height);

	FPfNode* RandomNode = &GetValue(RandomX, RandomY);

	return RandomNode;
}

bool APathfindingGrid::CoordinatesWalkable(FVector Target)
{
	int X, Y;

	if (GetCoordinatesFromWorldPosition(Target, X, Y))
	{
		if (GetValue(X, Y).IsWalkable)
		{
			return true;
		}
	}
	return false;
}

void APathfindingGrid::GenerateDynamicHeatMap(float DeltaTime)
{
	if (Delay <= 0)
	{
		for (int x = 0; x < Width; ++x)
		{
			for (int y = 0; y < Height; ++y)
			{
				GetValue(x, y).DynamicHeat = 0.f;
				// 	FVector WorldPosition;
				// 	GetWorldPositionFromCoordinates(x, y, WorldPosition);
				// 	bool Heat = false;
				// 	for (int i = 0; i < Offsets.Num(); ++i)
				// 	{
				// 		FHitResult Hit;
				// 		FVector OffsetWorldPosition = WorldPosition + Offsets[i];
				// 		FVector StartPosition = OffsetWorldPosition + FVector(0, 0, 10000);
				// 		FCollisionQueryParams CollisionQuery = FCollisionQueryParams();
				// 		if (GetWorld()->
				// 			LineTraceSingleByChannel(Hit, StartPosition, OffsetWorldPosition, ECC_GameTraceChannel9,
				// 			                         CollisionQuery))
				// 		{
				// 			if (!Cast<APlayerCharacter>(Hit.GetActor()))
				// 			{
				// 			}
				// 			Heat = true;
				// 		}
				// 	}
				// 	if (Heat)
				// 	{
				// 		GetValue(x, y).DynamicHeat = 10.f;
				// 		TArray Neighbors(GetNeighbors(x, y));
				// 		for (FPfNode* Neighbor : Neighbors)
				// 		{
				// 			Neighbor->DynamicHeat = 5.f;
				// 		}
				// 	}
				// }
			}
			TArray Enemies(FPersistentWorldManager::GetEnemies());

			for (ABaseCharacter* Enemy : Enemies)
			{
				int X, Y;
				if (GetCoordinatesFromWorldPosition(Enemy->GetActorLocation(), X, Y))
				{
					GetValue(X, Y).DynamicHeat = 10.f;
					TArray Neighbors(GetNeighbors(X, Y));
					for (FPfNode* Neighbor : Neighbors)
					{
						Neighbor->DynamicHeat = 5.f;
					}
				}
			}
		}
		Delay = 0.5f;
	}
	Delay -= DeltaTime;
}

void APathfindingGrid::GenerateStaticHeatMap()
{
	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			if (!GetValue(x, y).IsWalkable)
			{
				TArray<FPfNode*> Neighbours = GetNeighbors(x, y);
				for (FPfNode* Neighbour : Neighbours)
				{
					if (Neighbour->IsWalkable)
					{
						Neighbour->StaticHeat = 20.f;
					}
				}
			}
			if (GetValue(x, y).StaticHeat > 5.f)
			{
				TArray<FPfNode*> Neighbours = GetNeighbors(x, y);
				for (FPfNode* Neighbour : Neighbours)
				{
					if (Neighbour->StaticHeat < GetValue(x, y).StaticHeat)
					{
						Neighbour->StaticHeat = GetValue(x, y).StaticHeat / 2.f;
					}
				}
			}
		}
	}
}

void APathfindingGrid::GenerateNavmesh()
{
	TArray<FVector> Offsets;
	const float QuarterCellSize = CellSize / 2.5f;

	Offsets.Add(FVector::Zero());
	Offsets.Add(FVector(QuarterCellSize, 0, 0));
	Offsets.Add(FVector(-QuarterCellSize, 0, 0));
	Offsets.Add(FVector(0, QuarterCellSize, 0));
	Offsets.Add(FVector(0, -QuarterCellSize, 0));
	Offsets.Add(FVector(QuarterCellSize, QuarterCellSize, 0));
	Offsets.Add(FVector(-QuarterCellSize, -QuarterCellSize, 0));
	Offsets.Add(FVector(QuarterCellSize, -QuarterCellSize, 0));
	Offsets.Add(FVector(-QuarterCellSize, QuarterCellSize, 0));

	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			FVector WorldPosition;
			GetWorldPositionFromCoordinates(x, y, WorldPosition);
			bool HitB = false;
			bool Spawn = false;
			bool Heat = false;
			for (int i = 0; i < Offsets.Num(); ++i)
			{
				FHitResult Hit;
				FVector OffsetWorldPosition = WorldPosition + Offsets[i];
				FVector StartPosition = OffsetWorldPosition + FVector(0, 0, 10000);
				FCollisionQueryParams CollisionQuery = FCollisionQueryParams();
				if (GetWorld()->
					LineTraceSingleByChannel(Hit, StartPosition, OffsetWorldPosition, ECC_GameTraceChannel5,
					                         CollisionQuery))
				{
					HitB = true;
					break;
				}
				if (GetWorld()->
					LineTraceSingleByChannel(Hit, StartPosition, OffsetWorldPosition, ECC_GameTraceChannel7,
					                         CollisionQuery))
				{
					Heat = true;
				}
				if (GetWorld()->
					LineTraceSingleByChannel(Hit, StartPosition, OffsetWorldPosition, ECC_GameTraceChannel10,
					                         CollisionQuery))
				{
					Spawn = true;
				}
			}
			if (HitB)
			{
				if (GetValue(x, y).IsWalkable)
				{
					ToggleWalkable(x, y);
				}
			}
			if (Heat)
			{
				if (GetValue(x, y).IsWalkable)
				{
					GetValue(x, y).StaticHeat = 10.f;
				}
			}
			if (Spawn)
			{
				if (GetValue(x, y).IsWalkable && !GetValue(x, y).SpawnArea)
				{
					ToggleSpawnArea(x, y);
				}
			}
		}
	}
}

static constexpr int GStraight_Cost = 10;
static constexpr int GDiagonal_Cost = 14;

int APathfindingGrid::CalculateDistance(const int StartX, const int StartY, const int EndX, const int EndY) const
{
	const int XDist = abs(StartX - EndX);
	const int YDist = abs(StartY - EndY);
	const int RemainingDist = abs(XDist - YDist);
	return FMath::Min(XDist, YDist) * GDiagonal_Cost + RemainingDist * GStraight_Cost;
}

FPfNode* APathfindingGrid::GetLowestCostNode(TArray<FPfNode*>& OpenList)
{
	int Lowest = OpenList[0]->S;
	FPfNode* LowestNode = OpenList[0];
	for (FPfNode* Node : OpenList)
	{
		if (Node->S < Lowest)
		{
			Lowest = Node->S;
			LowestNode = Node;
		}
	}
	return LowestNode;
}

void APathfindingGrid::ToggleWalkable(int X, int Y)
{
	FPfNode* Node = &GetValue(X, Y);
	Node->IsWalkable = !Node->IsWalkable;
}

void APathfindingGrid::ToggleSpawnArea(int X, int Y)
{
	FPfNode* Node = &GetValue(X, Y);
	Node->SpawnArea = !Node->SpawnArea;
}

bool APathfindingGrid::CalculatePath(FPfNode* EndNode, TArray<FPfNode*>& Path, const bool Verbose) const
{
	Path.Add(EndNode);
	const FPfNode* Current = EndNode;
	while (Current->CameFrom != nullptr)
	{
		Path.Add(Current->CameFrom);
		Current = Current->CameFrom;
	}
	Algo::Reverse(Path);

	if (Verbose)
	{
		for (const auto Node : Path)
		{
			UE_LOG(LogTemp, Warning, TEXT("(%i|%i)"), Node->X, Node->Y);
		}
	}
	return true;
}

bool APathfindingGrid::GetCoordinatesFromWorldPosition(const FVector WorldPosition, int& X, int& Y) const
{
	const FVector RelativePoint = WorldPosition - GetActorLocation();
	X = RelativePoint.X / CellSize;
	Y = RelativePoint.Y / CellSize;
	return X < Width && Y < Height;
}

bool APathfindingGrid::GetWorldPositionFromCoordinates(const int X, const int Y, FVector& WorldPosition) const
{
	FVector Origin = GetActorLocation();
	Origin.X += (X + 0.5f) * CellSize;
	Origin.Y += (Y + 0.5f) * CellSize;
	WorldPosition = Origin;
	return X < Width && Y < Height;
}

TArray<FVector> APathfindingGrid::ConvertPathToWorldSpace(const TArray<FPfNode*>& Path, bool Verbose) const
{
	if (Verbose)
	{
		UE_LOG(LogTemp, Warning, TEXT("WS-Path"));
	}

	TArray<FVector> WorldSpacePath;
	for (const auto Node : Path)
	{
		FVector P;
		GetWorldPositionFromCoordinates(Node->X, Node->Y, P);
		WorldSpacePath.Add(P);

		if (Verbose)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *P.ToString());
			DrawDebugSphere(GetWorld(), P, 30.0f, 20, FColor::Red, false, 1);
			//DrawDebugDirectionalArrow()
		}
	}
	return WorldSpacePath;
}
