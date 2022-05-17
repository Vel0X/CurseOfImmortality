// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingGrid.h"

#include "CurseOfImmortality/BaseClasses/GameController.h"

APathfindingGrid::APathfindingGrid(): TBaseGrid<FPfNode>(30, 30)
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
	auto node = GetValue(2, 2);
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
				FColor Green = FColor(30, 255, 50, 80);
				FColor Red = FColor(255, 40, 50, 80);
				FColor C = GetValue(x, y).IsWalkable ? Green : Red;
				DrawDebugSolidBox(GetWorld(), WorldPosition, FVector(CellSize * 0.5f, CellSize * 0.5f, 0.1f), C, false);
			}
		}
	}
}

void APathfindingGrid::BeginPlay()
{
	Super::BeginPlay();

	static_cast<UGameController*>(GetGameInstance())->BindPathfindingGrid(this);
}

void APathfindingGrid::PrintGrid()
{
	for (int y = 0; y < Height; ++y)
	{
		FString s = "|";

		for (int x = 0; x < Width; ++x)
		{
			char C = GetValue(x, y).IsWalkable ? '0' : 'X';
			s += C;
			s += '|';
		}

		UE_LOG(LogTemp, Warning, TEXT("%s"), *s);

		//p
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

			const int TempGCost = Current->G + CalculateDistance(Current->X, Current->Y, Neighbor->X, Neighbor->Y);

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

void APathfindingGrid::GenerateNavmesh()
{
	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			FHitResult R;
			FVector WorldPosition;
			GetWorldPositionFromCoordinates(x, y, WorldPosition);
			FVector StartPosition = WorldPosition + FVector(0, 0, 1000);
			FCollisionQueryParams P = FCollisionQueryParams();
			if (GetWorld()->LineTraceSingleByChannel(R, StartPosition, WorldPosition,
			                                         ECollisionChannel::ECC_WorldStatic, P))
			{
				if (!Cast<APawn>(R.GetActor()))
				{
					TArray<FPfNode*> NodesToToggle = GetNeighbors(x, y);
					for (FPfNode* Node : NodesToToggle)
					{
						if (Node->IsWalkable)
						{
							ToggleWalkable(Node->X, Node->Y);
						}
					}
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
	return min(XDist, YDist) * GDiagonal_Cost + RemainingDist * GStraight_Cost;
}

FPfNode* APathfindingGrid::GetLowestCostNode(TArray<FPfNode*>& OpenList)
{
	int lowest = OpenList[0]->S;
	FPfNode* LowestNode = OpenList[0];
	for (FPfNode* Node : OpenList)
	{
		if (Node->S < lowest)
		{
			lowest = Node->S;
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

bool APathfindingGrid::CalculatePath(FPfNode* EndNode, TArray<FPfNode*>& Path, bool Verbose)
{
	Path.Add(EndNode);
	FPfNode* Current = EndNode;
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
