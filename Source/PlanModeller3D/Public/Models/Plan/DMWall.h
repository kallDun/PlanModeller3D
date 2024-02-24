#pragma once

#include "DMRoom.h"
#include "DMWall.generated.h"

USTRUCT(BlueprintType)
struct FDMWall
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString Id;

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	FString Description;

	UPROPERTY(BlueprintReadWrite)
	bool Enable;

	UPROPERTY(BlueprintReadWrite)
	bool Visible;

	UPROPERTY(BlueprintReadWrite)
	double Area;

	UPROPERTY(BlueprintReadWrite)
	double Thickness;

	UPROPERTY(BlueprintReadWrite)
	bool Connected;

	UPROPERTY(BlueprintReadWrite)
	bool ThicknessAvailability;

	UPROPERTY(BlueprintReadWrite)
	double Height;
	
	UPROPERTY(BlueprintReadWrite)
	double HeightFromFloor;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector2D> Points;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> CornersIds;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> WallDependentModelsIds;

	TArray<FVector2D> GetConnectedPoints(const FDMRoom& Room)
	{
		TArray<FVector2D> ConnectedPoints;
		for (const auto& Point : Points)
		{
			if (Room.Points.Contains(Point))
			{
				ConnectedPoints.Add(Point);
			}
		}
		return ConnectedPoints;
	}

	bool IsConnectedToRoom(const FDMRoom& Room)
	{
		return GetConnectedPoints(Room).Num() >= 2;
	}
};
