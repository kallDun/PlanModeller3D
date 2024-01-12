#pragma once

#include "DMRoom.generated.h"

USTRUCT(BlueprintType)
struct FDMRoom
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
	double Area;

	UPROPERTY(BlueprintReadWrite)
	double Height;

	UPROPERTY(BlueprintReadWrite)
	double HeightFromFloor;

	UPROPERTY(BlueprintReadWrite)
	bool Enable;

	UPROPERTY(BlueprintReadWrite)
	bool Visible;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector2D> Points;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FGuid> CornersIds;
};
