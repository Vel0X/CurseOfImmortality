// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

		for (int x = X - 1; x <= X + 1; ++x)
		{
			for (int y = Y - 1; y <= Y + 1; ++y)
			{
				if (x == X && y == Y)
					continue;

				if (!IsValid(x, y))
					continue;

				Neighbors.Add(&GetValue(x, y));
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
	FPfNode() : X(0), Y(0), CameFrom(nullptr)
	{
	}

	FPfNode(const int X, const int Y) : X(X), Y(Y), CameFrom(nullptr)
	{
	}

	void Reset()
	{
		H = 999999;
		G = 999999;
		S = 999999;
		CameFrom = nullptr;
	}

	int GetCombinedHeat() const
	{
		return StaticHeat + DynamicHeat;
	}

	int X = 0, Y = 0;
	FPfNode* CameFrom;
	int H = 0, G = 0, S = 0, StaticHeat = 0, DynamicHeat = 0;
	bool IsWalkable = true;
	bool SpawnArea = false;
};

UCLASS()
class CURSEOFIMMORTALITY_API APathfindingGrid : public AActor, public TBaseGrid<FPfNode>
{
	GENERATED_BODY()

public:
	APathfindingGrid();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void Print() override;
	virtual bool ShouldTickIfViewportsOnly() const override;

	void PrintGrid();
	void ToggleWalkable(int X, int Y);
	void ToggleSpawnArea(int X, int Y);

	UFUNCTION(BlueprintCallable)
	void GenerateNavmesh();
	UFUNCTION(BlueprintCallable)
	void GenerateStaticHeatMap();
	UFUNCTION(BlueprintCallable)
	void GenerateDynamicHeatMap(float DeltaTime);

	bool GetPath(int StartX, int StartY, int EndX, int EndY, TArray<FPfNode*>& Path, bool Verbose = false);
	bool GetPathWorldSpace(FVector Start, FVector End, TArray<FVector>& WorldSpacePath, bool Verbose = false);
	bool CalculatePath(FPfNode* EndNode, TArray<FPfNode*>& Path, bool Verbose = false) const;
	bool GetCoordinatesFromWorldPosition(const FVector WorldPosition, int& X, int& Y) const;
	bool GetWorldPositionFromCoordinates(const int X, const int Y, FVector& WorldPosition) const;
	bool CoordinatesWalkable(FVector Target);
	
	int CalculateDistance(int StartX, int StartY, int EndX, int EndY) const;

	FPfNode* GetRandomNodeInNavMesh();
	static FPfNode* GetLowestCostNode(TArray<FPfNode*>& OpenList);

	TArray<FVector> ConvertPathToWorldSpace(const TArray<FPfNode*>& Path, bool Verbose = false) const;
	
	float Delay;

	UPROPERTY(EditAnywhere)
	float CellSize = 100.0f;

	UPROPERTY(EditAnywhere)
	bool ShowNavGrid = false;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> DynamicTraceChanel;
};
