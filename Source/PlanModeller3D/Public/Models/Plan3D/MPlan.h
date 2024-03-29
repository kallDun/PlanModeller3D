// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MFurniture.h"
#include "MDoor.h"
#include "MRoom.h"
#include "MWall.h"
#include "MWindow.h"
#include "Models/Furnitures/Generation/FurnitureGenerationData.h"
#include "MPlan.generated.h"


USTRUCT(BlueprintType)
struct FMPlan
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMRoom> Rooms = {};

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMWall> Walls = {};

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMWindow> Windows = {};

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMDoor> Doors = {};
	
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FMFurniture> Furnitures = {};
	
	UPROPERTY(BlueprintReadWrite)
	FFurnitureGenerationData FurnitureGenerationData;
};
