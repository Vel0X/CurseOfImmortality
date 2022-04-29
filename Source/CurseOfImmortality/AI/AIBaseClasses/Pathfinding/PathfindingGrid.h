// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/clsocket/src/ActiveSocket.h"
#include "UObject/Object.h"
#include "PathfindingGrid.generated.h"

template <class T>
class TBaseGrid
{
public:
	virtual ~TBaseGrid()
	{
		delete Values;
	}

	TBaseGrid() : Width(1), Height(1)
	{
		Values = new T[Width * Height];
	}


	TBaseGrid(const int Width, const int Height) : Width(Width), Height(Height)
	{
		Values = new T[Width * Height];
	}

	virtual void Print()
	{
	}

	T& GetValue(const int X, const int Y)
	{
		return Values[GetIndex(X, Y)];
	}

	int GetIndex(const int X, const int Y) const
	{
		return Y * Width + X;
	}

	bool IsValid(const int X, const int Y) const
	{
		return X >= 0 && Y >= 0 && X < Width && Y < Height;
	}
	
	void SetValue(const int X, const int Y, const T& Value)
	{
		Values[GetIndex(X, Y)] = Value;
	}

	TArray<T*> GetNeighbors(const int X, const int Y)
	{
		TArray<T*> Neighbors;

		for (int x = X-1; x <= X+1; ++x)
		{
			for (int y = Y - 1; y <= Y + 1 ; ++y)
			{
				if(x == X && y == Y)
					continue;
				
				if(!IsValid(x,y))
					continue;

				Neighbors.Add(&GetValue(x,y));
			}
		}
		
		return Neighbors;
	}

protected:
	T* Values;
	int Width, Height;
};

struct FPfNode
{
	FPfNode()
	{
	}

	FPfNode(const int X, const int Y) : X(X), Y(Y)
	{
	}

	void Reset()
	{
		H = MAXINT;
		G = MAXINT;
		S = MAXINT;
		CameFrom = nullptr; 
	}

	int X = 0, Y = 0;
	FPfNode* CameFrom;
	int H = 0, G = 0, S = 0;
	bool IsWalkable = true;
};

UCLASS()
class CURSEOFIMMORTALITY_API AUPathfindingGrid : public AActor, public TBaseGrid<FPfNode>
{
	GENERATED_BODY()

public:
	AUPathfindingGrid();
	virtual void Print() override;

	bool GetPath(int StartX, int StartY, int EndX, int EndY, TArray<FPfNode*>& Path);
	int CalculateDistance(int StartX, int StartY, int EndX, int EndY) const;
	FPfNode* GetLowestCostNode(TArray<FPfNode*>& OpenList);
	bool CalculatePath(FPfNode* EndNode, TArray<FPfNode*>& Path);
	bool GetCoordinatesFromWorldPosition(const FVector WorldPosition, int& X, int& Y) const;
	bool GetWorldPositionFromCoordinates(const int X, const int Y, FVector& WorldPosition) const;
public:
	float CellSize;
};