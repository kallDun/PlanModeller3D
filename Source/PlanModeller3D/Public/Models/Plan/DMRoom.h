#pragma once

#include "DMRoom.generated.h"

USTRUCT()
struct FDMRoom
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
	double Area;

	UPROPERTY()
	double Height;

	UPROPERTY()
	double HeightFromFloor;

	UPROPERTY()
	bool Enable;

	UPROPERTY()
	bool Visible;

	UPROPERTY()
	TArray<FVector2D> Points;
	
	UPROPERTY()
	TArray<FGuid> CornersIds;
};
