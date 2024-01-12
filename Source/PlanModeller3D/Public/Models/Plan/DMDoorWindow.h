// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DMDoorWindow.generated.h"

USTRUCT(BlueprintType)
struct FDMDoorWindow
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FGuid Id;

	UPROPERTY(BlueprintReadWrite)
	FGuid WallId;

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	FString Description;

	UPROPERTY(BlueprintReadWrite)
	double Area;

	UPROPERTY(BlueprintReadWrite)
	bool Enable;

	UPROPERTY(BlueprintReadWrite)
	bool Visible;

	UPROPERTY(BlueprintReadWrite)
	double Width1;

	UPROPERTY(BlueprintReadWrite)
	double Width2;

	UPROPERTY(BlueprintReadWrite)
	double Indent1;

	UPROPERTY(BlueprintReadWrite)
	double Indent2;

	UPROPERTY(BlueprintReadWrite)
	double MinIndentInMeters;

	UPROPERTY(BlueprintReadWrite)
	bool ChangeSecondPairPlaces;

	UPROPERTY(BlueprintReadWrite)
	double Height;
	
	UPROPERTY(BlueprintReadWrite)
	double HeightFromFloor;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector2D> Points;

	UPROPERTY(BlueprintReadWrite)
	TArray<FGuid> CornersPair1Ids;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FGuid> CornersPair2Ids;
};
