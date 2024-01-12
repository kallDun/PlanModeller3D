#pragma once

#include "DMRoom.generated.h"

USTRUCT(BlueprintType)
struct FDMRoom
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	double Height;

	UPROPERTY(BlueprintReadWrite)
	double HeightFromFloor;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector2D> Points;

	UPROPERTY(BlueprintReadWrite)
	double Area;

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	FString Description;
	
	UPROPERTY(BlueprintReadWrite)
	FString Id;

	UPROPERTY(BlueprintReadWrite)
	bool Enable;

	UPROPERTY(BlueprintReadWrite)
	bool Visible;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> CornersIds;
};
