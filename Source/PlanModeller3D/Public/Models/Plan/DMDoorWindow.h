// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DMDoorWindow.generated.h"

USTRUCT()
struct FDMDoorWindow
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGuid Id;

	UPROPERTY()
	FGuid WallId;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Description;

	UPROPERTY()
	double Area;

	UPROPERTY()
	bool Enable;

	UPROPERTY()
	bool Visible;

	UPROPERTY()
	double Width1;

	UPROPERTY()
	double Width2;

	UPROPERTY()
	double Indent1;

	UPROPERTY()
	double Indent2;

	UPROPERTY()
	double MinIndentInMeters;

	UPROPERTY()
	bool ChangeSecondPairPlaces;

	UPROPERTY()
	double Height;
	
	UPROPERTY()
	double HeightFromFloor;

	UPROPERTY()
	TArray<FVector2D> Points;

	UPROPERTY()
	TArray<FGuid> CornersPair1Ids;
	
	UPROPERTY()
	TArray<FGuid> CornersPair2Ids;
};
