#pragma once

#include "DMWall.generated.h"

USTRUCT(BlueprintType)
struct FDMWall
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FGuid Id;

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
	TArray<FGuid> CornersIds;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FGuid> WallDependentModelsIds;
};
