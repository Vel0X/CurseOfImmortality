// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingGrid.h"

AUPathfindingGrid::AUPathfindingGrid(): TBaseGrid<FPfNode>(10, 10)
{
	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			SetValue(x,y, FPfNode(x,y));
		}
	}
}

void AUPathfindingGrid::Print()
{	
	TBaseGrid<FPfNode>::Print();
	auto node = GetValue(2,2);
	UE_LOG(LogTemp, Warning, TEXT("VALUE %d"), node.X);

}

static constexpr int GMaximumIterations = 100000;

bool AUPathfindingGrid::GetPath(int StartX, int StartY, int EndX, int EndY, TArray<FPfNode*>& Path)
{

	TArray<FPfNode*> OpenList, ClosedList;
	
	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			GetValue(x,y).Reset();
		}
	}
	
	
	int CurrentIterations = 0;
	
	FPfNode* StartNode = &GetValue(StartX, StartY);
	FPfNode* EndNode = &GetValue(EndX, EndY);
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
			CalculatePath(Current, Path);
			return true;
		}

		OpenList.Remove(Current);
		ClosedList.Add(Current);

		TArray<FPfNode*> Neighbors = GetNeighbors(Current->X, Current->Y);

		for (int i = 0; i < Neighbors.Num(); ++i)
		{
			FPfNode* Neighbor = Neighbors[i];
			if(ClosedList.Contains(Neighbor))
				continue;

			if(!Neighbor->IsWalkable)
			{
				ClosedList.Add(Neighbor);
				continue;
			}

			const int TempGCost = Current->G + CalculateDistance(Current->X, Current->Y, Neighbor->X, Neighbor->Y);
			
			if (TempGCost < Neighbor->G)
			{
				Neighbor->G = TempGCost;
				Neighbor->H = CalculateDistance(Neighbor->X, Neighbor->Y, EndNode->X, EndNode->Y);
				Neighbor->S = Neighbor->G + Neighbor->H;
				Neighbor->CameFrom = Current;

				if(!OpenList.Contains(Neighbor))
					OpenList.Add(Neighbor);
			}
		}
		
	}

	//no path found
	return false;
}

static constexpr int GStraight_Cost = 10;
static constexpr int GDiagonal_Cost = 14;

int AUPathfindingGrid::CalculateDistance(const int StartX, const int StartY, const int EndX, const int EndY) const
{
	const int XDist = abs(StartX - EndX);
	const int YDist = abs(StartY - EndY);
	const int RemainingDist = abs(XDist - YDist);
	return FMath::Min(XDist, YDist) * GDiagonal_Cost + RemainingDist * GStraight_Cost;
}

FPfNode* AUPathfindingGrid::GetLowestCostNode(TArray<FPfNode*>& OpenList)
{
	int lowest = OpenList[0]->S;
	FPfNode* LowestNode = OpenList[0]; 
	for (FPfNode* Node : OpenList)
	{
		if(Node->S < lowest)
		{
			lowest = Node->S;
			LowestNode = Node;
		}
	}
	return LowestNode;
}

bool AUPathfindingGrid::CalculatePath(FPfNode* EndNode, TArray<FPfNode*>& Path)
{
	Path.Add(EndNode);
	FPfNode* Current = EndNode;
	while(Current->CameFrom != nullptr)
	{
		Path.Add(Current->CameFrom);
		Current = Current->CameFrom;
	}
	Algo::Reverse(Path);
	return true;
}

bool AUPathfindingGrid::GetCoordinatesFromWorldPosition(const FVector WorldPosition, int& X, int& Y) const
{
	const FVector RelativePoint = WorldPosition - GetActorLocation();
	X = static_cast<int>(RelativePoint.X / CellSize);
	Y = static_cast<int>(RelativePoint.Y / CellSize);
	return X < Width && Y < Height;
}

bool AUPathfindingGrid::GetWorldPositionFromCoordinates(const int X, const int Y, FVector& WorldPosition) const
{
	FVector Origin = GetActorLocation();
	Origin.X += (X + 0.5f) * CellSize;
	Origin.Y += (Y + 0.5f) * CellSize;
	WorldPosition = Origin;
	return X < Width && Y < Height;
}
