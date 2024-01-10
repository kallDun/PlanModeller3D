#pragma once

#include "DMWall.generated.h"

USTRUCT()
struct FDMWall
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGuid Id;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Description;

	UPROPERTY()
	bool Enable;

	UPROPERTY()
	bool Visible;

	UPROPERTY()
	double Area;

	UPROPERTY()
	double Thickness;

	UPROPERTY()
	bool Connected;

	UPROPERTY()
	bool ThicknessAvailability;

	UPROPERTY()
	double Height;
	
	UPROPERTY()
	double HeightFromFloor;

	UPROPERTY()
	TArray<FVector2D> Points;
	
	UPROPERTY()
	TArray<FGuid> CornersIds;
	
	UPROPERTY()
	TArray<FGuid> WallDependentModelsIds;
};
